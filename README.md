# 项目简介
该项目旨在开发一个基于虚幻引擎5（UE5）的开放世界动作角色扮演游戏，灵感来源于《原神》。游戏将结合自由探索、角色扮演、战斗系统与任务系统，呈现一个生动且广阔的虚拟世界，供玩家沉浸其中并进行多样化的互动。

## 主要特色：
开放世界设计：游戏地图将以开放式设计为主，玩家可以自由探索各类环境，包括城市、森林、地下迷宫等。  
角色发展与战斗：玩家可以扮演多个具有独特技能和的角色，参与即时战斗，并通过任务提升角色的属性与装备。  
任务系统与剧情：具备任务系统，支持多个不同类型的任务，带来游戏的故事体验。  
UI与交互：以直观和流畅的界面设计为目标，玩家能够轻松管理背包、物品以及角色信息。  
# 成员分工
| 姓名   |    学号    | 分工   |
|:-------|-----:|:-------|
| 徐云鹏   | 2353583   | **敌人类的实现**   |
| 徐清鹏   | 2354281   | **角色类的实现**  |
| 刘震     | 2352471   | **HUD界面的实现**   |
| 陈艺龙   | 2352359   | **游戏保存、角色骨骼制作和动画的实现**   |
| 陈奕炫   | 2351892   | **地图的实现**   |
# 项目开发日志
## 2024年11月25日 
项目初始化   
•	全体成员开始学习使用UE5开发，初步掌握UE基本工作原理。  
•	确定项目目标：创建一个基于UE5的开放世界动作角色扮演游戏，灵感来源于《原神》。  
•	项目分工：定义了团队成员角色，包括角色开发、地图设计、任务系统、UI界面开发，敌人开发、背包和物品逻辑等，然后依据分工进行UE5的专项学习。 
## 2024年11月26日
•	下载并配置UE5.5环境和Visual Studio2022的配套编程环境，讨论并统一代码风格。    
•	安装github桌面版，配置ue项目的.gitignore文件，确保版本控制正常运行。安装git-lfs实现大文件如地图资产等成功上传。  
•	创建主分支 master，搭建基本项目框架，完成UE5项目初始化。   
## 2024年11月28日
基础功能搭建   
•	提交分支 Map，实现了初步地形生成功能，测试UE5的地形编辑工具，并尝试导入场景模块。   
•	在 Character_Develop 分支上导入了第一个基础角色模型，并完成了骨骼动画的绑定，测试了简单的站立和跑步动画。  
•	重定向角色动画后实现了第一个完整的角色。  
•	提交分支Enemy，初步确定了敌人类的组成与各个接口。  
## 2024年12月1日
基础系统开发  
•	实现基础角色移动控制，并加入第三人称视角摄像机控制功能。  
•	提交 GameSave 分支，实现了基础的存档与加载功能，包括玩家位置、背包物品和任务状态。  
•	完成Map分支，搭建了初始新手村地图。  
•	完善Enemy分支  
## 2024年12月2日
•	创建Map1分支，进行了天空场景的搭建，实现了彩虹以及日月的搭建  
•	完善Map1分支，实现了日夜交替变换功能  

## 2024年12月3日
地图生态扩展  
•	创建Map2 分支，开始进行地下龙洞地图搭建。  
•	创建初始小地图。  
•	创建测试物品，用于测试背包功能  
•	创建初版Inventory分支，以及拾取物品逻辑，把背包组件绑定在角色身上。  
敌人类优化  
•	重新确立了EnemyCharacter的构成，梳理了四种组件的继承关系。  
•	重构了Enemy类相关的组件与类。  
	
## 2024年12月5日
多角色系统  
•	在 MultipleCharacter 分支中，新增第二个角色——近战攻击角色。  
•	为两个角色分别设计了基础技能（近战角色的拳击、远程角色的魔法炮弹攻击）。  
•	实现初步角色切换功能，通过按键在两个角色之间无缝切换。  
•	为小地图增加迷雾效果。  
•	提交Map2分支，地下龙洞地图搭建成功。  
敌人实例创建  
•	创建了BP_E_Bear及相关类。  
## 2024年12月7日
UI设计  
•	添加了角色血条和蓝条显示，UI动态更新角色的生命值和能量值。  
•	为每个角色设计了独立的装备栏，允许玩家为角色装备武器和道具。  
•	优化了背包界面的设计  
•	实现了按键放大地图的功能，完善大地图小地图的迷雾效果。  
•	UI界面更新，能同时显示三个角色的生命值和能量值。  
敌人实例创建  
•	创建了BP_E_Bear及相关类。  
## 2024年12月8日
背包与道具  
•	更新提交 Inventory 分支，新增支持查看、使用和丢弃道具的功能。  
•	实现道具拾取功能，玩家可以在地图中收集资源并存入背包。  
•	创建Map4分支，着手搭建第三张地图古风遗迹。  
•	着手制作地图传送门功能。  
敌人组件完善  
•	完善了四种组件的继承，派生出若干组件。  
## 2024年12月10日
角色技能扩展  
•	在 MutipleCharacter 分支中为每个角色增加了新的技能：火属性角色的范围火焰攻击、远程角色释放炮弹。  
•	提交Map4分支，第三张地图搭建成功。  
•	地图传送门逻辑完成。  
敌人实例创建  
•	创建了使用新组件的BP_E_Snail及相关类。  
## 2024年12月12日
战斗系统  
•	在 Enemy 分支中，创建了第一个敌人模型（基础近战敌人），并实现简单的AI逻辑（巡逻与追击玩家）。  
•	为地图传送门增加材质，并在地图上放置。  
•	创建Map5分支，开始搭建最后两张地图。  
•	修复了小地图显示的一些bug。  
敌人组件创建  
•	派生出boss的相关组件  
## 2024年12月14日
战斗交互  
•	在角色与敌人之间添加战斗交互逻辑：攻击命中时扣除对方的血量。  
•	添加敌人死亡逻辑，敌人在血量降为0时触发死亡动画并消失。  
•	修复战斗中角色与敌人偶尔不触发攻击的问题。  
•	修复人物切换后小地图图标显示异常的问题。  
•	Map5分支提交，五张地图完成搭建  
## 2024年12月16日
地图兼容性与优化  
•	调整角色的移动逻辑以适应不同地形，解决了角色在斜坡上移动时卡顿的问题。  
•	创建finalmap分支，合并所有地图资源、每张地图小地图的调试、传送门的搭建。  
•	修复地图合并后的一系列bug。  
## 2024年12月18日
NPC与任务扩展  
•	在 Task 分支中开发了初步任务系统，支持简单的“接任务—完成任务—提交任务”流程。  
•	在 npc 分支中添加了第一个NPC模型，并实现了NPC与玩家的对话交互。  
•	扩展任务系统，NPC可以根据任务状态触发不同的对话。  
•	创建更多符合场景的物品，用于任务系统。  
•	实现物品与人物属性的交互，使用物品可以增加角色蓝量或血量。  
敌人实例创建  
•	初步构建了boss敌人BP_BE_Spider及相关类 
## 2024年12月19日
•	提交 Playcharacter 分支，与gameSafe进行衔接，确保能保存角色数据 ）  
•	新增一个BOSS级敌人，设计了多阶段战斗机制，包括强力技能和血量回复。  
•	新增烹饪模块，以及其和背包物品的交互。  
•	Boss类debug完成。  
## 2024年12月20日
最终整合  
•	修复已知BUG，包括战斗逻辑中的无效攻击和地图中部分道具无法拾取的问题。  
•	角色死亡逻辑实现。  
•	角色装备信息实现游戏保存功能。  
•	新增鱼塘钓鱼模块，实现与场景元素的交互。  
## 2024年12月21日
测试与收尾  
•	当前活跃分支为 npc，对所有NPC任务逻辑进行了全面测试，修复了一些任务未正确触发的问题。  
•	进行全局测试并记录需要优化的细节，为后续的开发迭代做准备。  
