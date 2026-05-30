# Tasks

- [ ] Task 1: 创建 Qt5 项目结构和基础文件
  - [ ] SubTask 1.1: 创建 CMakeLists.txt，配置 Qt5 Widgets 依赖
  - [ ] SubTask 1.2: 创建 main.cpp 入口文件
  - [ ] SubTask 1.3: 创建主窗口 MainWindow 类

- [ ] Task 2: 实现任务数据模型
  - [ ] SubTask 2.1: 定义 TaskStatus 枚举（Pending, Running, Completed, Failed）
  - [ ] SubTask 2.2: 定义 TaskCondition 结构体（条件类型 + 参数）
  - [ ] SubTask 2.3: 实现 Task 类（id, name, status, condition）
  - [ ] SubTask 2.4: 实现 TaskModel 类管理任务列表和连接关系

- [ ] Task 3: 实现图形视图组件
  - [ ] SubTask 3.1: 实现 TaskNodeItem（QGraphicsItem），绘制圆角矩形节点，显示任务名和状态
  - [ ] SubTask 3.2: 实现 ConnectionItem（QGraphicsItem），绘制带箭头的连线
  - [ ] SubTask 3.3: 实现 TaskGraphScene（QGraphicsScene），管理节点和连线的布局
  - [ ] SubTask 3.4: 实现 TaskGraphView（QGraphicsView），提供缩放和拖拽功能

- [ ] Task 4: 实现右键菜单和任务编辑功能
  - [ ] SubTask 4.1: 在 TaskNodeItem 上实现 contextMenuEvent
  - [ ] SubTask 4.2: 实现"添加任务"功能（弹出对话框输入任务名，插入到当前节点后）
  - [ ] SubTask 4.3: 实现"修改任务"功能（弹出对话框编辑任务名）
  - [ ] SubTask 4.4: 实现"删除任务"功能（从模型移除并更新视图）

- [ ] Task 5: 实现任务切换条件对话框
  - [ ] SubTask 5.1: 创建 TaskConditionDialog 类
  - [ ] SubTask 5.2: 实现条件类型选择（QComboBox）
  - [ ] SubTask 5.3: 实现动态参数输入（时间秒数 / 时间点 HH:MM:SS）
  - [ ] SubTask 5.4: 在连线上显示条件标识文本

- [ ] Task 6: 集成主界面并验证
  - [ ] SubTask 6.1: 在 MainWindow 中嵌入 TaskGraphView
  - [ ] SubTask 6.2: 添加示例数据（任务1 -> 任务2 -> 任务3）
  - [ ] SubTask 6.3: 编译运行验证基本功能

# Task Dependencies
- Task 3 depends on Task 2
- Task 4 depends on Task 2, Task 3
- Task 5 depends on Task 2, Task 3
- Task 6 depends on Task 1, Task 2, Task 3, Task 4, Task 5
