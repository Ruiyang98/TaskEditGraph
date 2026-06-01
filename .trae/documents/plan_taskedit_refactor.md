# TaskEdit 项目改进计划

## 项目现状分析

- 使用 CMake 构建，已开启 `AUTOMOC` / `AUTORCC` / `AUTOUIC`
- **当前没有任何 `.ui` 文件**，所有界面完全通过代码手动布局
- `TaskConditionDialog` 完全代码构建，包含 `QComboBox` + `QStackedWidget` + `QSpinBox` + `QLineEdit` + 按钮
- 添加任务在 `TaskGraphScene::onAddTask()` 中使用 `QInputDialog` 直接输入名称，流程原始
- `MainWindow` 代码简单，但在构造函数中直接 `new Task()` 创建示例数据

---

## 改进目标

### 目标1：能用 `.ui` 文件实现的界面尽量用 UI 实现
### 目标2：简化项目，封装添加任务的接口

---

## 实施步骤

### 步骤1：为 TaskConditionDialog 创建 `.ui` 文件

**文件：** `src/taskconditiondialog.ui`

- 在 Qt Designer 中设计等效界面：
  - `QLabel` + `QComboBox`（条件类型）
  - `QStackedWidget`（3页参数面板）
    - 第0页：顺序执行（显示"无额外参数"）
    - 第1页：持续时间（`QLabel` + `QSpinBox`，范围1~99999）
    - 第2页：开始时间（`QLabel` + `QLineEdit`，placeholder `HH:MM:SS`，正则校验）
  - `QDialogButtonBox`（确定/取消按钮）

- 修改 `taskconditiondialog.h`：
  - 移除手动声明的控件指针（除了需要在代码中访问的）
  - 添加 `Ui::TaskConditionDialog *ui;`

- 修改 `taskconditiondialog.cpp`：
  - 移除 `setupUi()` 中所有手动布局代码
  - 改为 `ui->setupUi(this)`
  - 保留信号连接（类型切换 → StackedWidget 换页）
  - 保留 `setCondition()` 和 `condition()` 的数据读写逻辑
  - 在构造函数中设置窗口标题

---

### 步骤2：创建添加任务对话框 `AddTaskDialog`（`.ui` + `.h`/`.cpp`）

**新增文件：**
- `src/addtaskdialog.ui`
- `src/addtaskdialog.h`
- `src/addtaskdialog.cpp`

**界面设计（.ui）：**
- 任务名称：`QLabel` + `QLineEdit`
- 任务状态：`QLabel` + `QComboBox`（Pending / Running / Completed / Failed）
- 条件设置：放一个 `QPushButton` "设置条件..."，点击弹出 `TaskConditionDialog`
- 按钮：`QDialogButtonBox`（确定/取消）

**业务逻辑（.cpp）：**
- `task()` 方法：返回构造好的 `Task` 对象指针
- 内部维护一个 `TaskCondition` 成员，点击"设置条件..."时编辑
- 确定时校验名称非空

---

### 步骤3：封装添加任务接口

**修改 `TaskModel`：**
- 添加高级接口：
  ```cpp
  Task* createTask(const QString &name, TaskStatus status = TaskStatus::Pending);
  bool addTaskWithDialog(QWidget *parent = nullptr, int afterIndex = -1);
  ```
- `addTaskWithDialog` 内部实例化 `AddTaskDialog`，执行后如果 Accepted 则调用 `addTask(newTask)`

**或者更推荐的方式：**
- 不将 UI 依赖引入 `TaskModel`，保持 `TaskModel` 纯净
- 而是在 `TaskGraphScene` 或新建 `TaskEditHelper` 中封装：
  ```cpp
  // TaskEditHelper.h
  class TaskEditHelper {
  public:
      static bool addTaskInteractive(TaskModel *model, QWidget *parent = nullptr, int afterIndex = -1);
      static bool editTaskInteractive(TaskModel *model, int index, QWidget *parent = nullptr);
  };
  ```

**最终选择：** 新建 `TaskEditHelper` 类（`src/taskedithelper.h` / `.cpp`），封装：
- `addTaskInteractive()` —— 弹出 `AddTaskDialog`，成功后添加到模型
- `editTaskInteractive()` —— 弹出编辑对话框（或复用 `AddTaskDialog`），更新模型

这样 `TaskModel` 保持数据层纯净，`TaskGraphScene` 中的 `onAddTask` / `onEditTask` 简化为调用 `TaskEditHelper` 的一行代码。

---

### 步骤4：替换 `TaskGraphScene` 中的原始任务操作

**修改 `TaskGraphScene`：**
- `onAddTask(int index)`：移除 `QInputDialog` 代码，改为调用 `TaskEditHelper::addTaskInteractive(m_model, nullptr, index)`
- `onEditTask(int index)`：移除 `QInputDialog` 代码，改为调用 `TaskEditHelper::editTaskInteractive(m_model, index)`
- 移除 `QInputDialog` 头文件包含

---

### 步骤5：简化 `MainWindow`

**修改 `mainwindow.cpp`：**
- 将示例数据创建抽取到私有方法 `createDemoTasks()` 或直接在 `main.cpp` 中初始化
- 示例数据不是核心逻辑，应该和窗口初始化分离

---

### 步骤6：更新 CMakeLists.txt

- `file(GLOB SOURCES src/*.cpp)` 已经会自动包含新的 `.cpp` 文件
- `.ui` 文件因为 `CMAKE_AUTOUIC ON` 会自动被处理，但需要确认是否在同一目录
- 确保 `taskconditiondialog.ui` 和 `addtaskdialog.ui` 放在 `src/` 目录下即可被 AUTOUIC 识别

---

## 文件变更清单

| 类型 | 文件路径 | 说明 |
|------|---------|------|
| 新增 | `src/taskconditiondialog.ui` | TaskConditionDialog 的 Qt Designer 界面 |
| 修改 | `src/taskconditiondialog.h` | 引入 `Ui` 命名空间，移除手动控件声明 |
| 修改 | `src/taskconditiondialog.cpp` | 移除手动布局，使用 `ui->setupUi` |
| 新增 | `src/addtaskdialog.ui` | 添加任务对话框界面 |
| 新增 | `src/addtaskdialog.h` | 添加任务对话框头文件 |
| 新增 | `src/addtaskdialog.cpp` | 添加任务对话框实现 |
| 新增 | `src/taskedithelper.h` | 任务编辑辅助类头文件 |
| 新增 | `src/taskedithelper.cpp` | 任务编辑辅助类实现 |
| 修改 | `src/taskgraphscene.cpp` | 使用 TaskEditHelper 替代原始 QInputDialog |
| 修改 | `src/taskgraphscene.h` | 移除不再需要的方法声明（如有） |
| 修改 | `src/mainwindow.cpp` | 分离示例数据创建逻辑 |
| 确认 | `CMakeLists.txt` | AUTOUIC 已开启，无需修改 |

---

## 预期收益

1. **界面可视化维护**：`.ui` 文件可以用 Qt Designer 直接编辑，布局调整更直观
2. **代码量减少**：`TaskConditionDialog::setupUi()` 约 60 行手动布局代码可被 `.ui` 替代
3. **添加任务流程封装**：从原始的 `QInputDialog` 升级为完整的 `AddTaskDialog`，支持名称、状态、条件一并设置
4. **关注点分离**：`TaskEditHelper` 封装交互逻辑，`TaskModel` 保持纯净数据管理，`TaskGraphScene` 只负责图形和信号转发
