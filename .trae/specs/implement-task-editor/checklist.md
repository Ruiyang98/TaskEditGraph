# Checklist

- [x] 项目结构：CMakeLists.txt 正确配置 Qt5 Widgets，项目可编译
- [x] 任务数据模型：Task 类包含 id、name、status、condition 属性
- [x] 任务数据模型：TaskModel 支持增删改查任务并维护连接关系
- [x] 任务节点绘制：TaskNodeItem 显示圆角矩形、任务名、状态文本
- [x] 任务状态颜色：Pending=灰、Running=绿、Completed=蓝、Failed=红
- [x] 连线绘制：ConnectionItem 绘制带箭头的贝塞尔曲线或直线
- [x] 图形布局：三个任务节点水平排列，节点间有箭头连线
- [x] 右键菜单：在任务节点上右键弹出菜单（添加/修改/删除/设置条件）
- [x] 添加任务：选择"添加任务"后在当前节点后插入新任务并更新视图
- [x] 修改任务：选择"修改任务"后弹出对话框可编辑任务名称
- [x] 删除任务：选择"删除任务"后移除节点并重新连接前后任务
- [x] 条件对话框：TaskConditionDialog 可选择三种条件类型
- [x] 条件参数：执行指定时间后切换可输入秒数；指定时间开始可输入 HH:MM:SS
- [x] 条件显示：连线上显示当前设置的条件文本标识
- [x] 主界面集成：MainWindow 嵌入 TaskGraphView，显示示例数据
