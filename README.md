# pipex
UNIX shell의 pipe, redirection, heredoc의 동작을 구현한 프로그램입니다. 시스템 함수를 사용하여 UNIX shell의 내부 동작 원리와 동일한 방식으로 동작합니다.

## Update
- heredoc에서 EOF처리 못하는 오류 수정
- 2개 이상의 파이프를 실행했을 때 제대로 처리되지 않는 오류 수정

## Usage
`make && ./pipex file1 cmd1 cmd2 file2`
- file1과 file2는 파일의 이름입니다.
- cmd1과 cmd2는 "셸 명령어 + 명령어 인자(들)'입니다.

## Features
- 기본적인 파이프, 리다이렉션 기능 구현
  - `$> ./pipex infile "ls -l" "wc -l" outfile`는 다음과 동일하게 동작합니다: `< infile ls -l | wc -l > outfile`
- 2개 이상의 연속된 파이프 기능 구현
- heredoc 기능 구현
  - - `$> ./pipex here_doc LIMITER cmd cmd1 file`는 다음과 동일하게 동작합니다: `cmd << LIMITER | cmd1 >> file`

## Peer Reviews
<img width="533" alt="image" src="https://github.com/nemotheswimmer/pipex/assets/88709878/65c7abd4-6b43-4169-a3c8-d37c6161d63b">
<img width="533" alt="image" src="https://github.com/nemotheswimmer/pipex/assets/88709878/9c0e9210-e1d4-45b2-b0cd-dcc5d0e5437c">
<img width="533" alt="image" src="https://github.com/nemotheswimmer/pipex/assets/88709878/d557fd4a-bf80-41e5-9e04-13b9894d8e45">

## Notion Post
코드에 대한 자세한 설명은 [pipex에 대한 노트](https://probable-perch-892.notion.site/pipex-c012703b380145f48b075ab0becf9124?pvs=4)에 있습니다.
