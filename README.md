# Server side framework based on Spring

## Features
* Spring framework
* MyBatis framework
* Maven build
* Wildfly
* PostgreSQL
* etc

----

## Installation

### JDK
#### Download [JDK](http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html) - (1.8 이상 설치)
- 해당 OS에 맞게 시스템 환경변수인 PATH, JAVA_HOME 등록

### Eclipse
#### Download [Eclipse](http://www.eclipse.org/download) - (버전은 Neon 으로 다운)
1. 원하는 위치에 압축 해제 후 실행
2. Eclipse 메뉴의 Help -> Eclipse Marketplace 를 실행 후 NodeJS로 검색
3. Nodeclipse 를 설치

### SVN
1. 이클립스를 실행한 후 Help -> Install New Software... -> Add...
2. Name: Subclipse
   Location: http://subclipse.tigris.org/update_1.10.x 를 입력한 후 Next를 눌러 설치

### Wildfly
#### Download [Wildfly](http://wildfly.org/downloads/)
1. 2016-08-19에 올라온 10.1.0.Final 버전 중 Description 이 Java EE7 Full & Web Distribution 인 ZIP파일을 다운
2. 다운받은 ZIP 파일을 C:\Wildfly\wildfly-10.1.0.Final 경로에 맞춰 압축 해제
3. 환경변수에 
   변수이름: JBOSS_HOME
   변수값: C:\Wildfly\wildfly-10.1.0.Final 을 추가
4. C:\Wildfly\wildfly-10.1.0.Final\bin 경로로 들어가 standalone.bat 을 실행한 후 http://localhost:8080 페이지가 뜨는지 확인
5. 사용자 계정 추가 설정   
   1) C:\Wildfly\wildfly-10.1.0.Final\bin 경로로 들어가 add-user.bat 을 실행   
   2) a를 선택하여 administrator 계정을 설정 (개인이 원하는 id/pw로 설정해도 무방)   
   3) 엔터 -> Username, Password 입력 -> 엔터 -> 'yes' -> 'no'   
       - administrator id: admin   
       - administrator pw: whdlstm (조인스)   
   4) C:\Wildfly\wildfly-10.1.0.Final\bin 경로로 들어가 standalone.bat 을 실행한 후 http://localhost:9990/console 페이지에서 로그인이 되는지 확인   

#### JNDI setting
1. [Microsoft jdbc download](https://www.microsoft.com/ko-KR/download/details.aspx?id=11774) 에서 압축된 드라이버 패키지를 다운로드한 후 압축 해제
2. C:\Wildfly\wildfly-10.1.0.Final\bin 경로로 들어가 standalone.bat 을 실행
3. Wildfly admin console 접속 (ex. http://localhost:9990) 후 wildfly 설치 중 메모한 admin 계정으로 로그인
4. 상단의 메뉴 중 Deployments 에서 Add -> Next -> 파일선택 -> 압축을 푼 드라이버 패키지 경로에서 ...\sqljdbc_6.0.8112.100_kor.tar\sqljdbc_6.0\kor\jre8 에서 sqljdbc42.jar 선택 -> Next -> Finish
5. standalone.bat 재실행 후 Wildfly admin console 접속
6. Menu의 Configuration -> Subsystems -> Datasources -> Non-XA -> Datasoure 의 Add 버튼 클릭 후 JNDI 설정   
   1) Microsoft SQLServer Datasource 선택 -> Next   
   2) Next   
   3) 상단의 탭 중 Detected Driver 에서 sqljdbc42.jar 선택 -> Next   
   4) Connection URL: jdbc:sqlserver://10.50.102.13:1509;DatabaseName=SR0DB   
      Username: apSRBgen1   
      Password: whdlstm1!   설정 후 Next   
   5) Finish   
   6) Test Connection 을 했을 때 성공되면 테스트DB와 연결 완료   

### Nodejs
#### Download [NodeJS](https://nodejs.org/en/download/) - (버전 node-v6.10.3)
1. 자신의 OS에 맞는 Installer를 다운로드 받아 설치
2. Command prompt 에서 node 명령어가 작동되는지 확인

### Redis
#### Download [Redis](https://github.com/MSOpenTech/redis/releases) - (Windows_x64_3.2.100 버전)
1. 해당 페이지의 Downloads에서 Redis-x64-3.2.100.msi를 다운받아 설치 진행
2. cmd을 실행 후 redis가 설치된 폴더로 이동 후 다음 명령어를 입력
```
    > redis-server
    > redis-server --service-install
```
3. 설치 확인
```
    > redis-server --service-start
    > redis-cli
    > ping
    결과 > pong
    > exit
    > redis-server --service-stop
```
4. auth 확인
```
   > redis-cli -p 679
   127.0.0.1:6379> config get requirepass
   1) "requirepass"
   2) ""
   127.0.0.1:6379> config get requirepass whdlstm
   (error) ERR Wrong number of arguments for CONFIG get
   127.0.0.1:6379> config set requirepass whdlstm
   OK
   127.0.0.1:6379> config geet requirepass
   (error) NOAUTH Authentication required.
   127.0.0.1:6379> auth whdlstm
   OK
   127.0.0.1:6379> config get requirepass
   1) "requirepass"
   2) "whdlstm"
```
----

## Import

#### Project import
1. 이클립스를 실행한 후 [참조](http://devmonster.tistory.com/38)를 참고하여 '3.저장소에서 프로젝트 가져오기' 이후를 따라 진행
2. SVN Repository URL - https://XXX.XXX.XXX.XXX/svn/JIMS/JIMS_SRC/trunk

#### First build for web
1. Download [GIT](https://git-scm.com/downloads) - 설치
2. Command prompt 실행
3. 프로젝트의 해당 폴더의 web으로 이동 cd C:\workspace\prototype\web
4. npm install
5. npm install -g gulp

----

## Build and deploy

### Modify pom.xml
- ...\was 밑에 있음

```
   <plugin>
      <groupId>org.wildfly.plugins</groupId>
      <artifactId>wildfly-maven-plugin</artifactId>
      <version>1.0.2.Final</version>
      <configuration>
          <hostname>localhost</hostname>
          <port>9990</port>
          <username>wildfly 설치 중 메모한 정보 입력</username>
          <password>wildfly 설치 중 메모한 정보 입력</password>
      </configuration>
  </plugin>
```

### Modify applicationContext-jdbc.xml
- ...\was\src\main\resources\spring\applicationContext-jdbc.xml

```
   <bean id="dataSource" class="org.springframework.jndi.JndiObjectFactoryBean">
        <property name="jndiName" value="java:/MSSQLDS" />
        <property name="resourceRef" value="true" />
   </bean>
```

### Build and deploy project

#### Server side build
1. standalone.bat 실행 (C:\Wildfly\wildfly-10.1.0.Final\bin)
2. pom.xml 을 마우스 오른쪽 버튼으로 클릭
3. Run as ... -> 2. Maven build 선택
4. Base directory에 \was 경로추가 (예시: ${project_loc:프로젝트 dir명}\was)
5. Goal에 clean install wildfly:deploy 입력 후 실행

#### Client side build
1. gulp serve (로컬 실행)
2. gulp serve:dist (로컬 실행 및 배포용 소스 생성)
3. gulp release (배포용 소스 생성)

#### [Angularjs 구동순서]
1. Wildfly Server Start
2. Maven build 실행
3. 개발 Web Site 폴더 이동 gulp serve 실행,  background 실행시 nohup gulp serve &
4. gulp 서버가 구동되지 않을경우
   : node –v 확인, npm –v 확인
5. node js 가 설치않됬을 경우
   : Node js 다운로드 설치
   : Npm install
   : Npm install –g gulp
----

#### [WINDOWS PHP 실행시 mysql_init() 오류해결]
 1. PHP설치 폴더의 php.ini 파일을 Windows 폴더 밑으로 잘라내어 붙여넣기 후 Apache 서버를 restart함.
----

#### [JNI ]
1. javac Class 파일 생성
2. javah 로 jni.h 파일 생성 후 c++ 프로그램 개발

#### [.Net Quartz]
1. NuGet 패키지 관리에서 Quartz 설치
2. 프로젝트 파일에 참조 위치에 Quartz.dll 확인
3. 현재 IIS Setting 후 페이지 실행시 Quartz동작만 확인함. Quartz 동작을 Spring이나 다른 프레임웍을 통해 동작될수있도록 개발해야함.

#### [WSL 개발]

#### [guacamol-server 설치]
* linux Ubuntu 개발시 오류 체크
configure: error: "libpng is required for writing png messages" 오류 발생시
[VNC]
apt-get install libvncserver-dev
[RDP]
apt-get install libfreerdp-dev libvorbis-dev
[SSH]
apt-get install libssh-dev libpango1.0-dev

설치 진행
1. $ sudo apt-get install make gcc g++ libcairo2-dev libjpeg-turbo8-dev libpng-dev libtool-bin libossp-uuid-dev libavcodec-dev libavutil-dev libswscale-dev freerdp2-dev libpango1.0-dev libssh2-1-dev libvncserver-dev libtelnet-dev libssl-dev libvorbis-dev libwebp-dev
2. 다운로드 경로 및 압축파일
$ wget https://downloads.apache.org/guacamole/1.2.0/source/guacamole-server-1.2.0.tar.gz
3. 압축해제
$ tar -xvf guacamole-server-1.2.0.tar.gz
$ cd guacamole-server-1.2.0
4. 설치
$ ./configure --with-init-dir=/etc/init.d
5. 설치 순차적 처리
$ sudo make
$ sudo make install
6. ldconfig 명령을 실행하여 관련 링크를 만들고 Guacamole 서버 디렉터리의 가장 최근 공유 라이브러리에 캐시합니다.
$ sudo ldconfig
7. Guacamole 서버를 실행하기 위해 Guacamole Daemon (guacd)을 시작하고 부팅시 활성화하고 표시된대로 상태를 확인합니다.
$ sudo systemctl start guacd
$ sudo systemctl enable guacd
$ sudo systemctl status guacd 
8. Tomcat 서버는 브라우저를 통해 서버에 연결하는 사용자에게 Guacamole 클라이언트 콘텐츠를 제공하는 데 사용되므로 필수 사항입니다. 다음 명령을 실행하여 Tomcat을 설치하십시오.
$ sudo apt install tomcat9 tomcat9-admin tomcat9-common tomcat9-user
9. 설치시 Tomcat 서버가 실행 중이어야합니다. 다음과 같이 서버의 상태를 확인할 수 있습니다.
$ sudo systemctl status tomcat
10. Tomcat이 실행되고 있지 않으면 부팅시 시작하고 활성화합니다.
$ sudo systemctl start tomcat
$ sudo systemctl enable tomcat
11. 기본적으로 Tomcat은 포트 8080에서 실행되며 UFW가 실행중인 경우 다음과 같이이 포트를 허용해야합니다.
$ sudo ufw allow 8080/tcp
$ sudo ufw reload
12. Tomcat 서버가 설치된 상태에서 사용자가 서버에 연결할 수있는 Java 기반 웹 애플리케이션 인 Guacamole 클라이언트 설치를 진행합니다.
먼저 그림과 같이 구성 디렉토리를 생성합니다.
$ sudo mkdir /etc/guacamole
13. 그림과 같이 명령을 사용하여 Guacamole 클라이언트 바이너리를/etc/guacamole 디렉토리에 다운로드합니다.
$ sudo wget https://downloads.apache.org/guacamole/1.2.0/binary/guacamole-1.2.0.war -O /etc/guacamole/guacamole.war
14. 다운로드가 완료되면 다음과 같이 Tomcat WebApps 디렉토리에 대한 심볼릭 링크를 만듭니다.
$ ln -s /etc/guacamole/guacamole.war /var/lib/tomcat9/webapps/
15. 웹 앱을 배포하려면 Tomcat 서버와 Guacamole 데몬을 모두 다시 시작합니다.
$ sudo systemctl restart tomcat9
$ sudo systemctl restart guacd
Guacamole과 관련된 두 가지 주요 구성 파일이 있습니다. "Guacamole에서 사용하는/etc/guacamole 및 /etc/guacamole/guacamole.properties 파일 및 확장 기능입니다.
16. 계속하기 전에 확장과 라이브러리를위한 디렉토리를 만들어야합니다.
$ sudo mkdir /etc/guacamole/{extensions,lib}
17. 다음으로 홈 디렉토리 환경 변수를 구성하고/etc/default/tomcat9 구성 파일에 추가합니다.
$ sudo echo "GUACAMOLE_HOME=/etc/guacamole" >> /etc/default/tomcat9
18. Guacamole이 Guacamole 데몬 (guacd)에 연결하는 방법을 결정하기 위해 그림과 같이 guacamole.properties 파일을 생성합니다.
$ sudo vim /etc/guacamole/guacamole.properties
아래 내용을 추가하고 파일을 저장하십시오.

guacd-hostname: localhost
guacd-port:     4822
user-mapping:   /etc/guacamole/user-mapping.xml
auth-provider:  net.sourceforge.guacamole.net.basic.BasicFileAuthenticationProvider
19. 다음으로 브라우저의 웹 인터페이스를 통해 Guacamole에 연결하고 로그인 할 수있는 사용자를 정의하는 user-mapping.xml 파일을 생성합니다.

그렇게하기 전에 표시된대로 로그인 사용자에 대한 해시 된 암호를 생성해야합니다. 강력한 암호를 자신의 암호로 바꾸십시오.

$ echo -n yourStrongPassword | openssl md5
이와 같은 것을 얻어야합니다.

(stdin)= efd7ff06c71f155a2f07fbb23d69609
해시 된 비밀번호를 복사하여 user-mapping.xml 파일에 필요하므로 어딘가에 저장하십시오.

20. 이제 user-mapping.xml 파일을 만듭니다.

$ sudo vim /etc/guacamole/user-mapping.xml
아래 내용을 붙여 넣으세요.

<user-mapping>
    <authorize 
            username="tecmint"
            password="efd7ff06c71f155a2f07fbb23d69609"
            encoding="md5">

        <connection name="Ubuntu20.04-Focal-Fossa>
            <protocol>ssh</protocol>
            <param name="hostname">173.82.187.242</param>
            <param name="port">22</param>
            <param name="username">root</param>
        </connection>
        <connection name="Windows Server">
            <protocol>rdp</protocol>
            <param name="hostname">173.82.187.22</param>
            <param name="port">3389</param>
        </connection>
    </authorize>
</user-mapping>
온라인 상태 인 2 개의 원격 시스템에 연결할 수 있도록 두 개의 연결 프로필을 정의했습니다.

Ubuntu 20.04 Server – IP: 173.82.187.242 via SSH protocol
Windows Server – IP: 173.82.187.22 via RDP protocol
21. 변경 사항을 적용하려면 Tomcat 서버와 Guacamole을 다시 시작합니다.

$ sudo systemctl restart tomcat9
$ sudo systemctl restart guacd
지금까지 Guacamole 서버와 클라이언트가 구성되었습니다. "이제 브라우저를 사용하여 Guacamole 웹 UI에 액세스 해 보겠습니다.

22. Guacamole 웹 UI에 액세스하려면 브라우저를 열고 다음과 같이 서버 주소를 검색합니다.

http://server-ip:8080/guacamole

23. user-mapping.xml 파일에서 지정한 자격 증명을 사용하여 로그인합니다. 로그인하면 모든 연결 섹션 아래의 버튼에 나열된 파일에서 정의한 서버 연결을 찾을 수 있습니다.
24. Ubuntu 20.04 LTS 서버에 액세스하려면 연결을 클릭하면 원격 Ubuntu 서버에 대한 SSH 연결이 시작됩니다. 암호를 입력하라는 메시지가 표시되고 암호를 입력하고 ENTER를 누르면 그림과 같이 원격 시스템에 로그인됩니다.
-------------------------------

## PRO-C
proc iname=pc_card_use_load
gcc -c pc_card_use_load.c
gcc -o pc_card_use_load pc_card_use_load.o -L$ORACLE_HOME/lib -ldl -lm -lclntsh

## KEY
2GVN2-4CQT3-WDF7R-HCT2Y-VQ2JX-BGYANG
