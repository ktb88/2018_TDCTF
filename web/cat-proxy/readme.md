# CAT Proxy
## Information
- Web

## 서버에서 제공해주는 정보
1. X

## 존재하는 취약점
1. LFI
2. Unserialize
3. SSRF

## 공격 방법
1. LFI를 통해 소스코드 릭
2. 릭한 코드를 통해 MySQL의 계정 정보를 얻을 수 있음
3. 페이지에 회원가입하여 Nyaa 페이지를 통해 Port Scan 가능 - MySQL
4. Profile 페이지에 있는 file_exists 함수의 취약점을 이용
5. phar파일을 업로드하여 Deserialize 공격 및 SSRF를 통해 Flag 획득
