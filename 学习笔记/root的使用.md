# Using of root in Ubuntu 22.04

To perform system-level tasks in Ubuntu 22.04, you can use the **sudo** command, which will ask you for your own password to authenticate yourself. If you set up your own user account during the Ubuntu installation and added that account to the sudo user group, then your user account will be authorised to execute sudo commands.

If you do need to enable the root user and set a password in Ubuntu, you can use the following steps:

## 1、Chang the key of root in Ubuntu

### i. Log in as root user

```bash
sudo -i
```

### ii. Set key to root

```bash
passwd
```

Reset the key following the prompts

### iii. Make sure that root user has the key enable

```bash
passed -u root
```



## 2、Use of root

### i. Turn to root user

1. If you know the password of root user, you can log in with su

   ```bash
   su
   ```

2. If you wanna log in with sudo, here's the code

   ```bash
   sudo -i
   ```

### ii. Enter your password

### iii. Installation of software packages

```bash
apt install package_[name]
```

### iv. Create a user

```bash
useradd newuser
```

### v. Check and edit the file

```bash
vi /etc/filename.conf
```

### vi. Manage system services

```bash
systemctl start servicename
systemctl stop servicename
systemctl restart servicename
systemctl reload servicename
systemctl status servicename
systemctl enable servicename
systemctl disable servicename
systemctl list-unit-file --type=sercice | grep enable
```

### vii. Update the system

```bash
apt update
apt upgrade
```

### viii. Return to normal user

```bash
exit
```

