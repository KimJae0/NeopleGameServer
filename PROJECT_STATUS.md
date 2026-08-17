# Project Status

## Project
NeopleGameServer

## Goal
C++ 기반 멀티플레이 게임 서버를 구현하여
네오플 서버 프로그래머 포트폴리오로 활용한다.

## Current Environment
- OS: Windows
- Compiler: MSVC 19.37
- C++ Standard: C++20
- Build System: CMake
- Generator: Visual Studio 17 2022
- Debugger: GDB / Visual Studio Debugger 활용 예정

---

## Day 0 - Development Environment

### Completed
- Git repository initialized
- GitHub repository connected
- `.gitignore` configured
- CMake project created
- C++20 configured
- MSVC build environment verified
- Debug executable successfully built and executed

---

## Day 1 - Server Core Structure

### Goal
게임 서버의 기본 객체 구조를 설계하고
Server / Player / Session 간의 관계를 구현한다.

### Completed

#### Player
- Player class 구현
- Player ID 관리
- Position 관리
- HP 관리
- PlayerState 관리
- `Move()`
- `TakeDamage()`
- 상태/위치 조회 함수 구현

#### Session
- Session class 구현
- Session ID 기반 관리 구조 설계
- Player ID 연결 정보 관리
- `ConnectPlayer()`
- `GetPlayerId()`

#### Server
- Player 관리
- Session 관리
- `std::unordered_map` 기반 객체 관리
- Player 추가/삭제/조회
- Session 추가/조회
- 자동 Session ID 생성

### Current Structure

Server
- `unordered_map<int, Player> players`
- `unordered_map<int, Session> sessions`
- `int nextSessionId`

Session
- `int playerId`

Player
- `int ID`
- `int X`
- `int Y`
- `int HP`
- `PlayerState State`

### Verification

실행 결과:

Player 101: 100 200 30 Alive
Session 1 -> Player 101

### Learned Concepts
- Header / Source 분리
- Class / Constructor
- Encapsulation
- Object / Pointer
- Iterator
- `unordered_map`
- `find()`
- `emplace()`
- `nullptr`
- `enum class`
- `struct`
- CMake source/include directory configuration

---

## Day 2 - TCP Network Server

### Goal
TCP Socket을 이용하여 Client와 실제 연결을 수립하고
Session과 TCP Connection을 연결한다.

### Completed

#### Winsock
- `WSAStartup()`을 통한 Winsock 초기화
- `WSACleanup()`을 통한 종료
- `SOCKET` 타입 이해

#### Server Socket
- `socket()`을 이용한 TCP Socket 생성
- `sockaddr_in`을 이용한 Server 주소 설정
- `htons()`를 이용한 Port 설정
- `inet_addr()`를 이용한 IP 설정
- `bind()`를 이용한 주소 연결
- `listen()`을 이용한 연결 대기
- `accept()`를 이용한 Client 연결 수락

#### Client
- 별도의 `NeopleGameClient.exe` 생성
- Client Socket 생성
- `connect()`를 이용한 Server 연결
- `send()`를 이용한 데이터 송신
- `recv()`를 이용한 데이터 수신

#### Session
- Client Connection Socket 저장
- `Send()` 구현
- `Receive()` 구현
- Session과 실제 TCP Connection 연결

### Current Network Structure

Server
- `ListeningSocket`
  - 새로운 Client 연결을 받는 용도
- `sessions`
  - Client별 Session 관리

Session
- `ClientSocket`
  - 특정 Client와 실제 데이터 송수신
- `playerId`
  - 연결된 Player 정보

Client
- `clientSocket`
  - Server와 TCP 통신

### Network Flow

Client:

connect()
↓
Server ListeningSocket
↓
accept()
↓
Server Connection Socket
↓
Session 생성
↓
Session::Receive()
↓
Session::Send()

### Verification

실제 TCP Echo 통신 성공.

Server:

```text
Server Listening...
Player 101: 100 200 30 Alive
Client connected!
Hello Server
Session ID: 1


## Day 3 - Packet Processing

### Goal
TCP Byte Stream을 게임 Packet으로 처리하고
Packet을 실제 Player 상태 변경으로 연결한다.

### Completed

#### Packet
- PacketHeader 구현
- PacketType 정의
- MovePacket 구현
- Packet Size / Type 관리

#### Packet Sending
- Client에서 MovePacket 생성
- 구조체 데이터를 TCP Socket으로 전송

#### Packet Receiving
- Session::Receive() 구현
- ReceiveBuffer 구현
- TCP Stream 기반 데이터 누적
- PacketHeader 크기 확인
- Packet 전체 수신 여부 확인
- PopPacket() 구현
- 처리한 Packet을 ReceiveBuffer에서 제거

#### Packet Parsing
- PacketHeader Type 확인
- MovePacket 파싱
- MovePacket의 X/Y 값 확인

#### Game State Integration
- Session과 Player 연결
- Session의 Player ID 조회
- Server::FindPlayer()를 통한 Player 조회
- MovePacket → Player::Move() 연결
- 실제 Player 위치 변경 검증

#### Session Processing
- ProcessSession() 함수 분리
- Client 연결 처리와 Session 데이터 처리 역할 분리

### Verification

Client:
- MovePacket
- X = 150
- Y = 300

Server:

```text
Packet: X=150 Y=300
Player: X=150 Y=300


## Day 4 - Multi Client & I/O Multiplexing

### Goal

Blocking `recv()` 기반의 단일 Client 처리 구조를 개선하여
여러 Client를 동시에 관리할 수 있는 서버 Event Loop를 구현한다.

또한 Client 연결 종료를 감지하고
Session과 Socket을 안전하게 정리할 수 있도록 한다.

---

### Problem

Day 3에서는 `ProcessSession()`을 분리했지만
`Session::Receive()` 내부의 `recv()`가 blocking 방식으로 동작했다.

따라서 하나의 Client가 데이터를 보내지 않고 대기하면
해당 Client의 `recv()`에서 서버가 멈추게 된다.

```text
Client A
connect
↓
recv() 대기
↓
Client B의 연결/Packet 처리 불가능