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
3. 개발 Web Site 폴더 이동 gulp serve 실행
4. gulp 서버가 구동되지 않을경우
   : node –v 확인, npm –v 확인
5. node js 가 설치않됬을 경우
   : Node js 다운로드 설치
   : Npm install
   : Npm install –g gulp
----
