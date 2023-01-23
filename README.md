# Operating System
|project| description |
|:---:|:---:|
| [:two:](#xv6에-system-call-추가) | xv6에 system call 추가 |
| [:three:](#xv6에-ssu-scheduler-구현) | xv6에 SSU Scheduler 구현 |
| [:four:](#page-replacement-simulator) | page replacement simulator |


## xv6에 system call 추가
### xv6 커널 이해
- `user.h` : XV6의 시스템 호출 정의
- `usys.S` : XV6의 시스템 호출 리스트
- `syscall.h` : 시스템 호출 번호 매핑
- `syscall.c` : 시스템 호출 인수를 구문 분석하는 함수 및 실제 시스템 호출 구현에 대한 포인터
- `syspro.c` : 프로세스 관련 시스템 호출 구현
- `proc.h`: struct proc 구조 정의
- `proc.c` : 프로세스 간의 스케줄링 및 컨텍스트 전환을 수행하는 함수
### memsize 시스템 콜 추가 및 이를 호출하는 간단한 쉘 프로그램 구현
호출한 프로세스의 메모리 사용량을 출력하는 `memsize()` 시스템 콜 구현
  - 커널 모드의 `myproc()` 사용
- memsizetest 쉘 프로그램을 통해 memsize 시스템 콜 실행 확인
### trace 시스템 콜 추가 및 이를 호출하는 간단한 쉘 프로그램 구현
- 추적할 시스템 콜을 지정하는 정수 `mask`를 인자로 받음
- trace 시스템 콜은 호출한 프로세스와 이후 생성하는 모든 자식 프로세스에 대한 trace mask를 활성화해야 하고, 다른 프로세스에는 영향을 미치지 않음
- ssu_trace 쉘 프로그램을 통해 trace 시스템 콜 실행 확인
  - `ssu_trace [mask] [command]` 형식으로 실행
### 실행 결과
- `memsize` 실행 결과
  - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214059570-6e8fd417-4360-4be9-8c57-5a84074937da.png">
  - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214059754-27c11f95-0fb1-49ae-bc06-c36079e77ec2.png">
- `trace` 결과
  - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214059965-60e2a54a-1bb8-4c2b-abc3-17bf27c294d5.png">

## xv6에 SSU Scheduler 구현
### 스케줄링
- 다중 프로그래밍을 가능하게 하는 운영체제 커널의 기본 기능
- 기존 xv6의 스케줄링 기법은 다음 실행할 프로세스를 선택할 때 process table을 순회하며 RUNNABLE 상태인 프로세스를 순차적으로 선택하는 방식
- 스케줄링 함수 구현이 목표이므로 CPU 코어 개수를 1개로 제한
### SSU Scheduler 구현
- 프로세스 실행 흐름에서 새로 생긴 프로세스가 제외되지 않도록 큰 가중치를 부여하는 스케줄러
- 모든 프로세스는 각자의 가중치(weight) 및 우선순위(priority)를 가짐
- priority 값은 스케줄링 함수가 호출될 때마다 다음과 같은 규칙에 따라 업데이트됨
  - new_priority = old_priority + (time_slice / weight)
  - time_slice = 10,000,000ns
- 스케줄링 함수는 다음 실행될 프로세스로 RUNNABLE 상태인 프로세스 중 가장 낮은 priority 값을 가진 프로세스를 선택
- weight 값은 프로세스 생성 순서에 따라 1부터 차례대로 증가시키며 부여함
- 가장 낮은 priority 값은 struct ptable의 멤버로 관리하며, 스케줄링 함수가 호출될 때마다 new_priority와 함께 갱신됨

### sdebug 명령어 및 weightset 시스템 콜 구현
- `sdebug`: 스케줄링 함수의 동작 과정을 확인할 수 있도록 PID, 프로세스 가중치, 프로세스 생성 후부터 해당 명령어에 의해 프로세스 정보가 출력되기까지 소요된 시간을 출력
- `weightset`: 매개변수로 입력받은 값을 sdebug 명령어에 의해 생성되는 프로세스의 weight 값으로 부여하도록 구현

### 다음에 실행될 프로세스 선정 과정 디버깅 기능 구현
- xv6 빌드 시 `debug=1` 매개변수 전달을 통해, 스케줄링 함수에서 다음 실행될 프로세스를 선택할 때마다 PID, 프로세스 이름, 프로세스 가중치, 프로세스 우선순위 값을 출력하도록 구현

### 실행 결과
- `sdebug` 실행 결과
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214063368-4ee3ff56-40e9-4935-9eb2-bb839d5734bc.png">
- 디버깅 결과
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214063483-eacf469c-e8c9-4066-a6aa-e4e1d7c6c0ae.png">
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214063782-bc91df59-8e2a-4d03-8dd7-9fa2ec4f3cdd.png">
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214063887-8fd5f15e-57ec-440b-ad7b-544c0030ea37.png">
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214064003-281912d0-8447-4bd1-aba7-dec45d45e383.png">
   - <img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214064077-eecead8b-c581-4c6b-90d8-b1628f283cbb.png">

## Page Replacement Simulator
7가지 page replacement algorithm 구현
<details>
<summary> Optimal Algorithm</summary>
<div>

- 가장 오랫동안 쓰이지 않을 페이지를 교체하는 알고리즘이다. Page fault rate가 가장 낮은 이상적인 알고리즘이지만 실질적인 구현이 불가능하다. 실제 구현 가능한 알고리즘들을 평가하는 표준이 된다.   
- int 배열로 프레임 배열을 만들고 배열의 값을 모두 0으로 초기화한다.
REFERENCE_SIZE인 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다.   
- 프레임 배열 전체를 돌면서 해당 참조값이 있는지 검사하고, 있다면 Hit이므로 다음 참조값을 검사한다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 모두 차지 않았다면 빈 배열에 순서대로 참조값을 넣어준다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 모두 찼다면 해당 참조값의 인덱스부터 500까지 돌면서 각 프레임에 할당된 페이지가 언제 다시 쓰이는지 검사한다. 가장 나중에 쓰일 페이지를 찾아서 페이지를 교체한다.
</div>
</details>

<details>
<summary> FIFO Algorithm</summary>
<div>

- 메모리에 가장 오래 있었던 페이지를 교체하는 알고리즘이다. 구현이 쉽다는 장점이 있지만 `Belady's Anomaly`가 발생한다. `Belady's Anomaly`란 프레임 수를 늘렸는데 page fault rate가 증가하는 현상이다. 페이지가 사용될 시간을 이용하는 `Optimal algorithm`과 달리, `FIFO algorithm`은 페이지가 메모리로 들어온 시간을 이용한다.
- int형 배열로 프레임 배열을 만들고 배열의 값을 모두 0으로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 프레임 배열 전체를 돌면서 해당 참조값이 있는지 검사하고, 있다면 Hit이므로 다음 참조값을 검사한다. 해당 참조값이 프레임 배열에 없다면 현재 idx 변수가 가리키는 프레임을 교체한다. idx 변수는 모듈러 연산을 통해 0에서부터 1씩 증가한다.
</div>
</details>

<details>
<summary> LIFO Algorithm</summary>
<div>

- 메모리에 가장 짧게 있었던 페이지를 교체하는 알고리즘이다. 구현이 쉽다는 장점이 있지만 성능이 좋지 않다. 프레임에 페이지가 다 할당된 후부터는 마지막 프레임만 계속 교체된다.
- int형 배열로 프레임 배열을 만들고 배열의 값을 모두 0으로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 프레임 배열 전체를 돌면서 해당 참조값이 있는지 검사하고, 있다면 Hit이므로 다음 참조값을 검사한다. 해당 참조값이 프레임 배열에 없다면 현재 idx 변수가 가리키는 프레임을 교체한다. idx 변수는 프레임이 전부 찰 때까지 0에서부터 1씩 증가하다가 프레임이 가득 찬 이후로는 마지막 프레임만 가리킨다.
</div>
</details>

<details>
<summary> LRU Algorithm</summary>
<div>

- `Optimal algorithm`은 실제 구현이 불가능하지만, 예측을 통해 `LRU algorithm`은 구현할 수 있다. 가장 오래 사용되지 않은 페이지를 교체하는 알고리즘이다. 구현이 복잡하다는 단점이 있지만 Optimal에 가장 근사한 성능을 보인다. 각 페이지마다 counter 정보를 가지고 있으면서 페이지 참조가 있어날 때마다 갱신해줘야 하기 때문에 오버헤드가 증가한다.
- 단방향 연결 리스트로 프레임 구조체 포인터를 만들고 NULL로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 참조값과 노드의 페이지 변수값을 하나씩 검사한다. 두 값이 같다면 Hit이므로 다음 참조값을 검사한다. 현재 마지막 프레임이거나 비어있는 프레임일 경우 Hit 여부 검사 반복문을 탈출한다. 해당 참조값이 연결리스트에 없고 리스트가 다 차지 않았다면 새 노드를 할당한다. 할당된 새 노드는 맨 앞, 즉 head가 된다. 해당 참조값이 연결리스트에 없고 리스트가 다 찼다면 가장 뒤에 있는 노드의 page 변수 값을 요청이 들어온 page로 수정하고 맨 앞으로 만든다.
</div>
</details>

<details>
<summary> LFU Algorithm</summary>
<div>

- 가장 자주 접근되지 않은 페이지를 교체하는 알고리즘이다. page마다 0으로 초기화된 counter를 가지고 있으며 참조될 때마다 counter값이 증가한다. 메모리에 올라왔다가 victim이 되어 쫓겨날 땐 해당 page의 counter 값을 0으로 만든다. 다시 메모리에 올라올 경우 counter 값은 1이 된다. 접근 횟수만 보기 때문에 오래 전에 접근한 페이지의 counter 값이 높아 교체되지 않을 가능성이 있다.
- int형 배열로 프레임 배열과 counter 배열을 만들고 배열의 값을 모두 0으로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 프레임 배열 전체를 돌면서 해당 참조값이 있는지 검사하고, 있다면 Hit이므로 해당 참조값의 counter를 증가시킨 후, 다음 참조값을 검사한다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 가득 차지 않은 경우 순서대로 프레임에 값을 저장하고 counter 값을 1로 만든다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 가득 찬 경우 counter 값을 비교하며 가장 적게 사용된 프레임을 찾는다. 찾은 cictim 페이지를 교체하고 새로 온 페이지의 counter 값을 1로 만든다.
</div>
</details>

<details>
<summary> Second Chance Algorithm (One handed)</summary>
<div>

- R bit가 0이면 교체하는 알고리즘이다. 헤드 포인터가 가장 오래된 페이지를 가리키고 있으며 victim을 찾기 위해 한 페이지씩 R bit를 검사한다. R bit가 0이라면 바로 교체를 하고 포인터를 다음 프레임으로 이동시킨다. R bit가 1이라면 R bit를 0으로 바꾼 뒤 포인터를 다음 프레임으로 이동시킨다. 모든 페이지의 R bit가 1이라면 FIFO 알고리즘과 같아진다.
- 페이지 번호와 r_bit를 멤버로 갖는 프레임 구조체 배열을 만들고 각 멤버 값들을 0으로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 프레임 구조체 배열 전체를 돌면서 해당 참조값이 있는지 검사하고, 있다면 Hit이므로 다음 참조값을 검사한다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 다 차지 않았다면 순서대로 page와 r_bit 값을 저장한다. 해당 참조값이 프레임 배열에 없고 프레임 배열이 다 찼다면 r_bit가 1인지 0인지 검사한다. r_bit가 1이라면 r_bit를 0으로 바꾸고 다음 프레임을 검사한다. r_bit가 0이라면 페이지를 교체한다.
</div>
</details>

<details>
<summary> Enhanced Second Chance Algorithm</summary>
<div>

- R,W 비트를 사용해 우선순위를 정하고 이 우선순위를 바탕으로 페이지를 교체하는 알고리즘이다. 페이지 폴트 발생 시 들어오는 페이지의 R bit는 1, W bit는 페이지 수정 여부에 따라 결정한다. (R, W)는 (0, 0), (1, 0), (0, 1), (1, 1) 순의 우선순위를 갖는다. (1, 0)이 (0, 1)보다 낮은 우선순위를 갖는 이유는 read한 페이지에 다시 접근할 확률이 write한 페이지에 접근할 확률보다 높기 때문이다.
- 페이지 번호와 r_bit, w_bit를 멤버로 갖는 프레임 구조체 배열을 만들고 각 멤버 값들을 0으로 초기화한다. 500만큼 반복문을 돌면서 page replacement algorithm을 수행한다. 프레임 구조체 배열 전체를 돌면서 해당 참조값이 있는지 검사한다. 있다면 Hit이므로 해당 페이지의 r_bit는 1로, w_bit는 참조값의 w_bit에 따라 갱신하고 다음 참조값을 검사한다. 해당 참조값이 배열에 없고 프레임 배열이 다 차지 않았다면 순서대로 page와 r_bit, w_bit 값을 저장한다. 해당 참조값이 배열에 없고 프레임 배열이 다 찼다면 (R, W)가 (0, 0)인 페이지를 찾는다. 있다면 해당 페이지를 교체하고 없다면 (R, W)가 (0, 1)인 페이지를 찾는다. 있다면 해당 페이지를 교체하고 찾으면서 검사하는 페이지의 r_bit를 0으로 바꿔준다. 모든 프레임을 검사해도 없다면 다시 (0, 0), (0, 1)을 찾기를 반복한다. 
</div>
</details>

### 실행 결과
<img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214070086-3de8b90a-bb5e-490a-8112-ab724e27ce2a.png">
<img width="500" alt="image" src="https://user-images.githubusercontent.com/65652094/214070274-6c36e0d3-a778-4c60-aa55-608a1f02e034.png">
