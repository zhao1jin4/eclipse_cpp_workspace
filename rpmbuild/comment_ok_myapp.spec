#
# spec file for package myapp (Version 1.0)
#

Vendor:           Wrox Press
Distribution:     Any
Name:	          myapp
Release:          1
Packager:         neil@provider.com
License:	  Copyright 2007 Wiley Publishing, Inc.
Group:            Applications/Media
Provides:         myapp

#Requires:         mysql-3.23
#Requires:         mysql>=3.23
#表示依赖任何版本的mysql
Requires:         mysql

Autoreqprov:      on
Version:          1.0
Summary:          Trivial application

#Source:           myapp-1.0.tar.gz
#%{}是宏,在注释里也会被展开，对应前面的变量。
#默认找 ~/<当前.spec文件所在目录名>/SOURCES/ 目录下的文件
Source:           %{name}-%{version}.tar.gz

#Buildroot　在哪个目录构建，，设置后可使用变量$RPM_BUILD_ROOT　引用这个值，测试实际上不是？？
#值可以使用%{_tmppath},%{_bindir},%{_mandir}变量 
Buildroot:	%{_tmppath}/%{name}-%{version}-root

%description
MyAPP Trivial Application

A trivial application used to demonstrate development tools.

This version pretends it requires MySQL 3.23.

Authors: Neil Matthew and Richard Stones

%prep
%setup
#%setup -q 安静模式

%build
make

#%make_install 会调用make install
%install
#_tmppath=/var/tmp
echo "_tmppath=%{_tmppath}"

#_bindir=/usr/bin
echo "_bindir=%{_bindir}"

#_mandir=/usr/share/man
echo "_mandir=%{_mandir}"

#RPM_BUILD_ROOT=~/<当前.spec文件所在目录名>/BUILDROOT/myapp-1.0-1.x86_64
echo "RPM_BUILD_ROOT=${RPM_BUILD_ROOT}"


#make install　这样不行
mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p $RPM_BUILD_ROOT%{_mandir}/man1/
install -m755 myapp $RPM_BUILD_ROOT%{_bindir}/myapp
install -m755 myapp.1 $RPM_BUILD_ROOT%{_mandir}/man1/myapp.1
gzip $RPM_BUILD_ROOT%{_mandir}/man1/myapp.1


#%clean
make clean

%post
#安装前后执行的命令，这个没有被执行？
touch /tmp/rpmbuild_post.txt

#软件包中的所有文件
%files
#这个些是在目录~/<当前.spec文件所在目录名>/BUILDROOT/myapp-1.0-1.x86_64中找
/usr/bin/myapp
/usr/share/man/man1/myapp.1.gz
#%{_bindir}/myapp
#%{_mandir}/man1/myapp.1.gz

