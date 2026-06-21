# ft_printf

C 표준 라이브러리의 `printf()` 일부 기능을 직접 구현한 프로젝트.
자세한 설명은 [블로그 포스트](https://cryscham123.github.io/posts/02_categories/42_seoul/notes/00.html)를 참고해주세요.

## 지원 기능

- 변환 지정자: `c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`
- 플래그: `-`, `0`, `.`, `#`, `+`, 공백
- 필드 너비
- 정밀도
- 출력한 문자 수 반환
- 출력 실패 시 `-1` 반환

## 파일 구성

| 파일 | 설명 |
| --- | --- |
| `ft_printf.c` | `ft_printf()` 진입점, 서식 문자열 순회, 플래그/필드 파싱 |
| `parse.c` | 문자, 문자열, 정수, 16진수 출력 처리 |
| `flag_utils.c` | 패딩, 정밀도, 보조 유틸 함수 |
| `ft_printf.h` | 구조체, 플래그 매크로, 함수 프로토타입 |
| `Makefile` | 정적 라이브러리 빌드 규칙 |

## 빌드

```sh
make
```

빌드가 끝나면 현재 디렉터리에 `libftprintf.a`가 생성됩니다.

사용 가능한 Makefile 규칙은 다음과 같습니다.

```sh
make clean    # 오브젝트 파일 삭제
make fclean   # 오브젝트 파일과 libftprintf.a 삭제
make re       # fclean 후 다시 빌드
```

컴파일 옵션은 `-Wall -Werror -Wextra`입니다.

## 사용 예시

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("char: %c\n", 'A');
	ft_printf("str : %.5s\n", "hello world");
	ft_printf("int : %+05d\n", 42);
	ft_printf("hex : %#x\n", 255);
	ft_printf("ptr : %p\n", (void *)main);
	return (0);
}
```

예시 파일을 `main.c`로 작성했다면 다음처럼 컴파일할 수 있습니다.

```sh
make
cc -Wall -Werror -Wextra main.c libftprintf.a
./a.out
```
