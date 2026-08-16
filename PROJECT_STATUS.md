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

## Next Step

### Day 2 - TCP Network Server

목표:
- TCP Socket 기본 개념 학습
- Server Socket 생성
- `bind()`
- `listen()`
- `accept()`
- Client 연결 확인
- Session과 실제 TCP 연결의 관계 설계
- 간단한 Client ↔ Server 통신 구현

### Priority
1. TCP 기본 동작 이해
2. Socket API 이해
3. Client 연결 수락
4. 데이터 송수신
5. 기존 Session 구조와 연결

### Portfolio Focus
단순한 기능 구현보다
**네트워크 서버의 구조와 데이터 흐름을 설명할 수 있는 수준**을 목표로 한다.