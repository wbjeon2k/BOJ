---
layout: post
categories: ps
date: 2021-09-11 01:00 +0900
title: "PS 용 C++ 환경 구성 with VSCode"
---

<!--

For Almight blog:

---
tags: ps
date: 2021-09-11 01:00 +0900
title: "MIT OCW 알고리즘 강의 추천"
author: wbjeon2k
---

**author**: [wbjeon2k](https://wbjeon2k.github.io/) 
-->

## PS 용 C++ 환경 구성 with VSCode, MSYS2, Shell Script

필자는 최근 학교에서 랩 인턴을 수행하게 되었습니다.  

더블 모니터가 달린 호사스러운 환경에 기쁨도 잠시, 수 많은 초기 세팅에 정신을 잃고 말았습니다.  

특히 세팅이 99% 정도 끝났을 때, PATH 설정을 잘못 건드려서 포맷 후 다시 세팅을 할 때... 정말 어지러웠습니다.  

하지만, 알고리즘 PS 세팅은 이미 여러 환경에 설치 해 본 경험이 있기에 쉽게 할 수 있었습니다.  

제 알고리즘 PS 환경 설정, 그리고 실제로 제가 어떻게 그 환경을 쓰는지 공유하고자 글을 쓰게 되었습니다.  

더 좋은 방법이 있다면 제안 받아서 업데이트 하겠습니다. 많은 정보 공유 부탁드립니다!  

### 알고리즘 PS 환경 대전제

알고리즘 PS에 사용하는 주 언어가 C++ 라는 대전제가 있습니다.  

Python 등을 사용하는 분들 *( a.k.a 이단아, 힙스터)* 은 알아서 잘 하시리라 믿습니다.  

### What is VSCode?

[Visual Studio Code](https://code.visualstudio.com/)(이하 VSCode) 는 MS 에서 만든 오픈소스 코드 에디터 입니다. [VSCode Github](https://github.com/microsoft/vscode)  

[Visual Studio](https://visualstudio.microsoft.com/ko/downloads/) 가 훌륭한 에디터 기능을 가지고 있지만, IDE 라서 에디터로 쓰기에는 너무 무겁기에 알짜만 뽑아온 것이 초기 VSCode 입니다.  

이후 오픈소스 프로그램을 전폭적으로 지원하는 MS의 움직임에 힘입어, 요즘에는 웬만한 IDE 수준으로 개발 환경을 구축할 수 있습니다.  

VSCode 를 활용한 PS 환경설정의 장점을 소개하고, 자세한 구축 방법에 대해서 알려드리고자 합니다.  

### Why VSCode?

처음으로 코딩, 특히 C++ 코딩을 접하게 되었을 때 부터 VSCode 를 쓴 사람은 (거의) 없을것이라 예상됩니다.  
*저는 DevC++ 였습니다. -틀-*  

Codeblock 이나 DevC++, 순정 VS 등 다양한 C++ 환경 설정 선택지가 있지만, VSCode 만의 장점은 다음과 같습니다.  

- 환경설정 동기화  

많은 분들이 VSCode 최대 장점을 수 많은 extension 이라고 생각 하셨을텐데, 저는 환경설정 동기화를 먼저 뽑고 싶습니다.  

VSCode 에 MS 계정으로 로그인을 하고 설정 동기화를 허용하면,  

어느 PC/OS 환경에서 VSCode 를 사용 하더라도 같은 환경 설정을 유지하여 효율적으로 사용할 수 있습니다.  

랩 컴퓨터에 알고리즘 PS용 환경 구축을 할 때 동기화를 쓸 수 없었다면 어떤 일이 일어났을까요?  

수 많은 extension 들을 수동 설치하고 나면 폰트 설정, indent(4 space) 등 모든 설정을 수동으로 해줘야 합니다.  

이런 끔찍한 일을 겪지 않기 위해서 설정 동기화를 할 수 있다는 것은 VSCode 의 매우 큰 장점입니다.  

- Extensions

VSCode 에는 수 많은 extension 들이 지원됩니다. VSCode 의 최대 장점으로 꼽히는 특징입니다.  

하지만 `ctrl+shift+x` 를 누른 후 `C++` 를 검색하여 모든 extension 을 무지성으로 설치하는건 좋지 않습니다.  

MS 에서 공식 지원 하는 것들도 많지만, 서드 파티도 많기 때문에 서로 충돌하면 골치 아픕니다.  

제가 생각하는 필수적인 extension 들을 알려 드리도록 하겠습니다.  

1. [C/C++ by MicroSoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)  

설명 드릴 필요가 없다고 생각합니다.  

1. [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)

필수 extension 들을 한꺼번에 깔아주는 pack 입니다. MS 가 지원하는 순정 extension 입니다.  

1. [C/C++ Themes](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-themes)

코드 가독성을 높이기 위해서는 테마 설정이 필수라고 생각합니다. 이것 까지가 MS 순정 extension 입니다.  

1. [C++ Intellisense](https://marketplace.visualstudio.com/items?itemName=austin.code-gnu-global)

Intellisense 는 여러 IDE 나 에디터에서 지원을 하는 기능입니다.  

여러분들이 코딩을 할 때 사용하는 변수의 이름이나 함수의 이름 등을 추론하여, 유력 후보를 추천하는 시스템 입니다.  

VS 순정 Intellisense 가 정말 기똥차지만, VSCode 에는 VS 순정 Intellisense 가 지원되지 않습니다.  

꿩 대신 닭 으로 쓸만합니다. 없는것 보다는 훨씬 낫습니다.  

### What is Msys2?

[MSYS2](https://www.msys2.org/) 는 Window 환경에서 gcc 등을 (비교적)편하게 설치하도록 도와주는 프로그램 입니다.  

오픈 소스로 운영되고 있습니다.  

### Why GCC Compiler?

C++ 의 순정 컴파일러는 gcc 이고, gcc를 사용하는 것을 권장 드립니다.  

컴파일러에 따라서 같은 C++ 파일에서 만들어진 실행파일이 서로 다른 동작을 하는 경우가 있기 때문에,  

MSVC 에서는 허용이 되지만, gcc 에서는 허용이 되지 않는 매크로 사용이나 변수 설정 등으로 인해서  

올바른 풀이 임에도 불구하고 컴파일 에러, 실행 에러 들이 발생할 수 있습니다.  

혹은 그 반대의 상황이 발생할수도 있습니다.  

*보통 Visual Studio 의 기본 컴파일러는 순정 gcc가 아니라, MSVC 입니다.*  

### Why MSYS2  

순정 gcc는 윈도우에 빌트인 되어있지 않기때문에 별도 설치를 해야하는데, MSYS2의 도움이 없으면 설치 과정이 매우 귀찮습니다.  

VSCode 공식 안내 자료 [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp) 에서도 MSYS2 를 사용합니다.  

### How to use MSYS2

1. [MSYS2](https://www.msys2.org/) 링크에서 안내 하는대로 진행합니다. PATH 설정에 유의하세요.  

1. VSCode 에서 아무 cpp 파일을 작성하고, `ctrl shift b` 를 눌렀을 때, 빌드 옵션에 gcc 가 나오는지 확인합니다.  

1. 공식 홈페이지에서 설치하도록 하는 패키지 만으로는 부족한 경우가 있어서 추가 설치를 진행합니다.  아래 명령어를 실행합니다.  

`pacman -S --needed git wget mingw-w64-x86_64-gcc mingw-w64-x86_64-ninja mingw-w64-x86_64-cmake make mingw-w64-x86_64-python3`  

### Shell Script

