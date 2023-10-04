# GitHub 使用说明（自用）

本文仅涉及下载/上传文件的基础方法，嫌麻烦就去下一个乌龟

## 一、下载

### 1、创建一个空文件夹，并 cd 进入

```bash
mkdir MA
cd MA/
```

### 2、执行 git done 

```bash
git clone [git文件地址]
```

![下载地址](/run/user/1000/doc/65522f6d/46DBA13582F9B13ECA483E60D461930B.png)

#### 如果出现报错

Command 'git' not found - 没有安装 git驱动

```bash
# 执行
sudo apt install git
```



## 二、上传文件

### 1、创建新的仓库

![创建新仓库_01](/run/user/1000/doc/b2987d0c/56A1E788448EA69F94BA5F74193C0858.png)

![创建新仓库_02](/run/user/1000/doc/1610a3f4/147F2E1C5527BCD06C911C41CC0A4F46.png)

### 2、进入要提交文件所在的文件夹

```bash
git init	# 初始化仓库
git remote add origin [你的git仓库地址]	# 链接远端 git仓库
```

#### 查看是否已经链接好

```bash
git remote -v
```

### 3、将本目录下所有的文件上传至本地缓冲区

```bash
git add .	# 上传至 cached
```

#### 查看提交日志

```bash
git log		# 查看上传日志
```

#### 查看文件/文件夹在工作区/暂存区的状态

```bash
git status		# 查看状态
```

### 4、将本地缓冲区的文件上传至远端缓冲区

```bash
git commit -m "[本次上传的名称]"
```

#### 如果报“请告诉我您是谁

```bash
# 执行
git config --global user.email "[你的邮箱地址]"	# 声明邮箱
git config --global user.name "[随便写一个用户名]"	# 声明用户名

git config --list	# 可以查看刚才输入的信息
```

再次 commit 即可上传

### 5、将远端缓冲区的文件上传至库

```bash
git push -u origin [你的分支名称]
```

第一次上传时需要输入**密码**

#### 分支名称

##### i.   查看你的分支名称

```bash
git branch		# 查看分支名称
```

##### ii.   修改分支名称

```bash
git branch -M [你想改的名称]
```

#### 密码获取

github主页

setting -> Developer Settings -> Personal access tokens -> Fine-grained tokens

##### 添加一个新的Token/获取密码:

- ###### 命名

- 在 “Repository access” 中选择 “All repositories”

- 要是嫌麻烦就将 "Permission" 中的权限全都开到最高

- 保存

- 退回到 token 界面就会得到一串密码

![创建token_01](/run/user/1000/doc/3c39ef58/2AF8794B65FA31142B8E6F19C550AC50.png)

![创建token_02](/run/user/1000/doc/9eb8b7b8/C9F2DCCC449D036F8D0BAED3CB4030E5.png)