# README.md

## 📚 연구 주제 소개

---

**Fuzzing**은 프로그램에 **무작위의 데이터를 삽입**하여 **버그 및 취약점**을 찾아주는 기술이다. 
예를 들어, 프로그램에 들어가는 입력(표준입력 or 파일)을 변조시켜 정상적인 동작이 아닌, **crash를 유발시키거나 메모리 corruption**을 일으키는 테스트 사례를 찾는다.  Fuzzing 기술은 여러 취약점을 찾는데 아주 유용한 툴로써 최근에 활발하게 연구개발이 진행되어 왔다. 이 프로젝트는 fuzzing 기술을 적용하여 전에 알려지지 않았던 **여러 open-source 소프트웨어의 버그 및 실제 취약점**을 찾고,  **issue를 community에 제출하는 과제**를 수행하였다.

## 📚 연구 스케쥴

---

1. 1~2주차: AFL/AFL++의 parallelized fuzzing 기능과 leveldb에 대한 조사를
한다
a. AFL/AFL++ parallelized fuzzing:
i. [https://afl-1.readthedocs.io/en/latest/fuzzing.html#parallelized-fuzzing](https://afl-1.readthedocs.io/en/latest/fuzzing.html#parallelized-fuzzing)
ii. [https://aflplus.plus/docs/parallel_fuzzing/](https://aflplus.plus/docs/parallel_fuzzing/)
b. levelDB: [https://github.com/google/leveldb](https://github.com/google/leveldb)
2. 3~4주차: 실험 환경을 구축한다.
3. 5~6주차: 실제로 parallelized fuzzing을 수행하여 버그를 찾고, 패치를
생성하여 취약점을 고친다.
4. 7~8주차: 결과 리포트를 작성하고, 결과를 발표하고 새로 개발한 코드는
github에 공유하고 마무리한다.

## 📚 연구 리포트 전문

---

[연구 리포트 전문](https://www.notion.so/parallel-fuzzing-ba685025271045e28380ca505b9f87ab)

## 📚 연구 PPT 발표 자료

---

[확장 가능한 parallel fuzzing 인프라 구축 및 성능 비교 분석 최종 발표.pptx](README%20md%2028ad0ad5033f4f4197287ceaf53d6ace/%25ED%2599%2595%25EC%259E%25A5_%25EA%25B0%2580%25EB%258A%25A5%25ED%2595%259C_parallel_fuzzing_%25EC%259D%25B8%25ED%2594%2584%25EB%259D%25BC_%25EA%25B5%25AC%25EC%25B6%2595_%25EB%25B0%258F_%25EC%2584%25B1%25EB%258A%25A5_%25EB%25B9%2584%25EA%25B5%2590_%25EB%25B6%2584%25EC%2584%259D_%25EC%25B5%259C%25EC%25A2%2585_%25EB%25B0%259C%25ED%2591%259C.pptx)

## 📚 Repository 주요 파일 소개

연구 리포트의 순서에 맞게 디렉토리를 정리하였습니다.

- [1] **AFLPlusPlus** ⇒ AFL++ fuzzer 파일
    
              test-instr.c ⇒ afl fuzzer test 파일
    
- [2] **leveldb** ⇒ leveldb fuzzing과 관련된 파일들 모음
    
              afl_in(leveldb_fuzz_input) ⇒ 코드 및 fuzz를 실행할 때 필요한 input 파일
    
              src ⇒  Fuzzing 할 때, 사용 했던 코드(cpp)파일
    
              libleveldb.a ⇒ compile 할 때 필요한 파일
    
    crash가 발견되지 않아 afl_out 폴더를 넣지 않았습니다
    
- [3-1-3] xpdf ⇒ xpdf fuzzing과 관련된 파일들 모음
    
              afl_in(xpdf_fuzz_input) ⇒ fuzz를 진행할 때 필요한 input 파일
    
              afl_out(xpdf_fuzz_output) ⇒ fuzz를 진행할 때 생성된 output 파일
    
- [3-1-2] tcpdump ⇒ tcpdump fuzzing과 관련된 파일들 모음
    
              afl_in(tcpdump_fuzz_input) ⇒ fuzz를 진행할 때 필요한 input 파일
    
              afl_out(tcpdump_fuzz_output) ⇒ fuzz를 진행할 때 생성된 output 파일
    
- [3-1-3] libtiff ⇒ libtiff fuzz를 진행하고 나온 LCOV report 파일
    
    
- [3-2] **vlc** ⇒ vlc fuzzing과 관련된 파일들 모음
    
             fuzzing_vlc(3.0.7_noPATCH) ⇒ CVE-2019-14776번 취약점의 패치를 진행하지 않고 fuzz를 진행한 vlc 3.0.7
    
             fuzzing_vlc(3.0.7_PATCHED) ⇒ CVE-2019-14776번 취약점의 패치를 진행하고 fuzz를 진행한 vlc 3.0.7
    
             fuzzing_vlc(3.0.8_PATCHED) ⇒ CVE-2019-14776번 취약점의 패치를 진행되고 fuzz를 진행한 vlc 3.0.8
    
    **vlc 공통 파일**<br>
    
    **afl_in(xpdf_fuzz_input)** ⇒ fuzz를 진행할 때 필요한 input 파일<br>
    **afl_out(xpdf_fuzz_output)** ⇒ fuzz를 진행할 때 생성된 output 파일<br>
    **Partial_instrumentation ⇒** fuzz를 진행할 때 함수명과 파일이름이 일치하는 것들만 접근하도록 함<br>
    **vlc-demux.run.c ⇒** 버그가 발생하는 실행코드
