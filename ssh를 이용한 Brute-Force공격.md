# 2020-2
review

< SSH를 이용한 무차별대입공격 > + kali-linux

ssh를 이용한 Brute-Force공격 과정
공격자VM IP주소 : 192.168.123.55 (칼리 리눅스)
공격대상VM IP주소 : 192.168.123.58 (칼리 리눅스)
--------------------------------------------------
무차별 대입 공격인 Brute-Force Attack으로 공격대상 시스템 root계정의 ID와 비밀번호를 알아내어 SSH원격 접속을 시도해보겠다.
우선 SSH를 이용한 터널링 기능을 이용했다. 리눅스 서버의 경우 SSH가 설치되어 있다. SSH는 보안이 유지되는 원격 접속을 위해 개발되었다. 즉, 데이터 통신의 암호화 기능을 제공한다.
**(공격대상VM)**
#sudo apt-get install leafpad로 leafpad를 설치해주었다.

 <img width="206" alt="14공격대상VM_ssh설치(우선)" src="https://user-images.githubusercontent.com/77279316/104564100-d9d62680-568d-11eb-84f4-900cd86feace.png">
 
#sudo leafpad /etc/ssh/sshd_config로 sshd_config파일을 열고, Port 22앞의 주석인 ‘#’을 제거하면 아래와 같다.

<img width="299" alt="15공격대상VM_sshd_config파일에서 주석삭제(우선)" src="https://user-images.githubusercontent.com/77279316/104564221-ff633000-568d-11eb-8068-cd39752c1d61.png">
<img width="298" alt="16공격대상VM_sshd_config파일에서 authontication수정" src="https://user-images.githubusercontent.com/77279316/104564270-0c801f00-568e-11eb-9a8c-b592397dd347.png">

root계정으로 로그인이 필요하기 때문에 위의 사진을 보면, /etc/ssh/sshd_config파일의 인증부분의 PermitRootLogin을 ‘yes’로 변경해주었다.
<img width="319" alt="1공격대상VM9p, 터널링_SSH설치" src="https://user-images.githubusercontent.com/77279316/104564557-64b72100-568e-11eb-9967-1ba47f61b998.png">

위의 사진처럼 설정을 마치면 #sudo /etc/init.d/ssh restart 로 ssh서비스를 재시작한다. 그리고 #ps -ef | grep sshd명령어로 확인해보면 /usr/sbin/sshd프로세스가 확인되는 것을 알 수 있다. 그럼 SSHD서비스가 설치된 것이다. 혹은 #nestat -ntl 을 실행하여 네트워크 연결을 확인할 수도 있다. 이 때, tcp6포트번호 22번이 Litsten모드이면 정상 작동함을 알 수 있는 것이다.
또한 실행 후, #service ssh start로 서비스 중인 프로그램을 확인하면 아래와 같다.

<img width="148" alt="2공격대상VM10p,서비스중인 프로그램확인" src="https://user-images.githubusercontent.com/77279316/104564702-95975600-568e-11eb-875b-3756648d9751.png">
<img width="153" alt="3ssh실행중" src="https://user-images.githubusercontent.com/77279316/104564721-9af4a080-568e-11eb-9ac1-882ac052c780.png">

#service –status-all로 확인해보면 ssh앞에 [+]로 실행 중임을 알 수 있다.

**(공격자VM)**
공격자 칼리리눅스VM에서 DBMS(DataBaseManagementSystem)시작 후, 관리자계정으로 접근하기 위해 #sudo -i를 해주었다.
#service postgresql start명령어로 데이터베이스를 시작한다. 이것을 시작하지 않고 진행하면 나중에 메타스플로잇에서 공격 모듈을 검색할 때 오류나 지연 현상이 발생할 수 있다.
#msfconsole로 메타스플로잇 콘솔을 실행하면 아래와 같은 화면이 나온다.

<img width="388" alt="17공격자VM DBMS시작후, msfconsole실행(re)" src="https://user-images.githubusercontent.com/77279316/104564883-cecfc600-568e-11eb-9d1d-b7b9b85cb76e.png">

위와 같이 메타스플로잇 프레임워크가 정상적으로 실행되면 msf5>명령어 콘솔이 나온다.
_(Payloads는 공격 후 대상 시스템에 연결하거나 대상 서버에 서비스설치와 같은 특정 작업 등을 수행하는데에 사용됨 / Auxiliary는 대상 네트워크에 정보 수집, 데이터베이스 포트 스캔 및 배너정보 수집 같은 특정 작업을 수행하는 보조 모듈 / Encoders는 페이로드 및 공격 벡터를 인코딩하여 바이러스 탐지 솔루션 또는 방화벽으로 탐지를 피하는 데에 사용됨)_ 
#use scanner/ssh/ssh_version으로 ssh_version모듈을 실행하여 타깃을 스캐닝한다. 그 후 rhost에 타깃의 IP범위를 지정한다. 이때, 환경설정파일마다 IP주소 대역이 다른데, 여기선 CIDR표기방법을 이용하고, 192.168.123.0/24는 192.168.123.0~255까지의 IP주소를 스캐닝한다는 의미이다. 또한, multi-thread를 50으로 지정하여 빠른 스캐닝이 가능하게 하고, 아래의 사진을 보면 #show options를 통해 설정이 의도대로 바뀐 것을 확인할 수 있다.
 
<img width="465" alt="18공격자VM_타깃스캐닝(re)" src="https://user-images.githubusercontent.com/77279316/104565032-050d4580-568f-11eb-8f89-114cb3015e7f.png">

#run으로 스캐닝을 시작하면 IP주소가 192.168.123.58인 호스트가 검색되는 것을 알 수 있다.
<img width="469" alt="19공격자VM_run으로 스캐닝시작(re)" src="https://user-images.githubusercontent.com/77279316/104565084-16eee880-568f-11eb-809e-da560e7387cc.png">

#use auxiliary/scanner/ssh/ssh_login명령어를 이용해 보조 기능 모듈로 SSH로그인을 사용한다. 여기서 auxiliary는 스캐닝 등 정보 수집을 목적으로 사용되는 모듈이다.
#show options실행으로 설정을 확인하면 아래와 같다. Description을 보면, ssh로그인 시도, 즉 Brute Force공격을 시행할 수 있는 모듈이다.

<img width="470" alt="20공격자VM14p_설정확인(re)" src="https://user-images.githubusercontent.com/77279316/104565131-2a01b880-568f-11eb-906a-38435d38dc0e.png">


공격을 시행하기 전에, 시도하고자 하는 ID파일과 PW파일을 사전에 준비한다.
leafpad명령어를 이용하기 위해서 먼저 #sudo apt-get install leafpad를 해준다. Leafpad는 메모장같은 역할을 한다. 이후에 아래와 같이 #sudo leafpad /home/jwock/Desktop/pw.txt로 바탕화면의 위치에 텍스트파일을 만든다. 

<img width="344" alt="12공격자VM_leafpad로 텍스트파일만들기(pw)" src="https://user-images.githubusercontent.com/77279316/104565262-5f0e0b00-568f-11eb-98ce-70fe82b61b37.png">


그럼 pw.txt파일이 열리고 아래의 사진과 같이 하나의 행에 기본적으로 root, admin, 실제 비밀번호 등을 함께 적어 password리스트가 담긴 파일로 저장한다.

<img width="301" alt="22공격자VM_leafpad 텍스트파일(pw내용)" src="https://user-images.githubusercontent.com/77279316/104565314-751bcb80-568f-11eb-923e-9a6f4d0c9373.png">


마찬가지로 id.txt파일도 user리스트가 담긴 파일로 만들어주면 된다.
이제 공격 모듈을 설정할 일만 남았다.
 
<img width="324" alt="10공격자VM_공격모듈설정_시작하면(re)" src="https://user-images.githubusercontent.com/77279316/104565463-aa281e00-568f-11eb-8aa6-f89a86d09002.png">

위의 사진을 차례대로 보면, 공격대상 IP주소인 192.168.123.58을 설정한다. 그 후 차례대로 바탕화면 위치에 있는 Password와 ID사전파일의 경로를 지정해주고, 공격속도를 5로 지정한다. 또한 공격대상의 ID와 PW를 찾으면 공격을 멈추도록 설정하고, Multi-thread도 50으로 맞추어 빠르게 스캐닝할 수 있도록 해주었다.
 
<img width="469" alt="19공격자VM_run으로 스캐닝시작(re)" src="https://user-images.githubusercontent.com/77279316/104565557-c7f58300-568f-11eb-8ab3-50c115d6f675.png">

이제 #run으로 공격을 시작하면 위와 같이 뜬다. 첫째 줄에, ‘Success : ‘jwock:5470’’이 뜨는 것을 보니 Brute-Force공격이 성공한 것을 알 수 있다.
마지막으로 #sessions명령어로 Session을 연결하면 공격대상VM을 확인할 수 있다.

<img width="470" alt="23공격자VM_session연결" src="https://user-images.githubusercontent.com/77279316/104565619-dc398000-568f-11eb-8bfe-d47e329483b5.png">


#sessions -i 1명령어로 1번 세션을 실행하여 세션 목록 확인할 수 있다.
**(공격대상VM)**
이전에 공격대상VM의 파일구조를 먼저 확인해보면 아래와 같다.

<img width="235" alt="24공격대상VM_파일구조(참고)" src="https://user-images.githubusercontent.com/77279316/104565831-389c9f80-5690-11eb-87cc-67711900cecb.png">


**(공격자VM)**
아래의 사진을 참고하면, 이제 이것을 공격자VM으로 확인할 수 있게 되었다.

<img width="329" alt="25공격자VM_공격대상 ls, pwd, whoami, ifconfig확인" src="https://user-images.githubusercontent.com/77279316/104565920-579b3180-5690-11eb-9bee-4ed0c85d34c2.png">

Brute Force공격을 성공하니, 위의 사진과 같이 공격자VM에서 공격대상VM의 파일구조, IP정보 등을 확인할 수 있게 되었다.
