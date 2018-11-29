# Kou
## Information
- Web

## 서버에서 제공해주는 정보
1. PHP 버전

## 존재하는 취약점
1. LFI
2. Simple Overflow

## 공격 방법
1. LFI를 통해 소스코드 릭
2. 릭한 소스코드를 통해 so파일을 로드해서 쓰는 것을 알수 있음
3. php.ini파일을 릭하여 so파일 위치 확인
4. LFI를 통해 so파일 추출
5. so파일 내에 존재하는 취약점 발견(Overflow)
6. kou 계정으로 로그인
7. Secret Data 글 열람 및 플래그 획득
