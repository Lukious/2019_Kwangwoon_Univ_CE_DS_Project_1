# 2019_Kwangwoon_Univ_CE_DS_Project_1
2019년도 광운대학교 컴퓨터정보공학부  데이터 구조 설계 및 실습 1차 프로젝트 정답 코드

과제 진행에 앞서 정기적으로 Update Notes 를 읽고 업데이트된 내용이 무엇이 있는지 확인하신 후 진행바랍니다.

### 좋은 질문들

[질문 1. BST 클래스의 "<<" operator 에서 m_root 를 접근하기 위해 함수를 정의하고 사용했더니 문법 오류가 발생합니다.](https://github.com/developer0hye/2019_Kwangwoon_Univ_CE_DS_Project_1/issues/2)

[질문 2. ShootForLog.txt 파일에 저장된 선수들의 데이터 중에서 각 줄의 끝에 ' ' 를 포함하는 경우가 존재합니다.](https://github.com/developer0hye/2019_Kwangwoon_Univ_CE_DS_Project_1/issues/3)

### 실습 자료

[4주차_Project1-1_v2](https://drive.google.com/open?id=1se_q3KILjjyU6YCZSmigngVlQf2g6lOX)

[5주차_Project1-2_v3](https://drive.google.com/open?id=15lZjqYUSXty3Ee3ZjAhQBbKkzCKvYwjW)

[6주차_Project1-3_v1](https://drive.google.com/open?id=1WID7APYCuKFpEJKfNpGQFRANXARZP62D)


## Update Notes

Please check this before you work on your project.

+) If you find some errors or any issues, feel free to upload the issue on this repository or contact by email.

robotmanyh@naver.com

quswngud3@kw.ac.kr

### 2019-09-10 

first upload

### 2019-09-14

remove the constructor in class ***BinarySearchTree***

```
BinarySearchTree(SoccerPlayerData& data); -> You don't need to implement and use this constructor.
```

### 2019-09-16

modified the implementation of operator "<<" in class ***TreeNode*** and add functions to access the *m_left* and *m_right*.

Before
```
...
friend std::ostream& operator<<(std::ostream& os, const TreeNode* node)
{
  // fill in your code to print in-order traversal of a binary search tree
	return os;
}
...
```

After
```
...
TreeNode* getLeftNode() const { return m_left; } -> newly added function, you don't need to use this function.
TreeNode* getRightNode() const { return m_right; } -> newly added function, you don't need to use this function.

friend std::ostream& operator<<(std::ostream& os, const TreeNode* node) -> you don't need to modify this function.
{
	os << node->m_data;
	return os;
}
...
```

### 2019-09-18

added condition to avoid accessing null pointer value in the operator "<<" in class ***TreeNode***

```
friend std::ostream& operator<<(std::ostream& os, const TreeNode* node)
{
	if(node != NULL) -> newly added condition
		os << node->m_data;
	return os;
}
```

remove the member function "void removePlayer(SoccerPlayerData data)" in class ***TransferWindowManager***

```
void removePlayer(SoccerPlayerData data); -> You don't need to implement and use this constructor.
```

### 2019-09-29

fixed the data format problem that some players contain space ' ' end of the line in "ShootForLog.txt".

for detail, refer to [this issue](https://github.com/developer0hye/2019_Kwangwoon_Univ_CE_DS_Project_1/issues/3).

### 2019-10-07

fixed the typing error in TransferWinidowManger.cpp

Midfilder -> Midfielder

## How to install?

Open the Ubuntu terminal and type the below commands.

```
sudo apt-get install git
git clone https://github.com/developer0hye/2019_Kwangwoon_Univ_CE_DS_Project_1.git
cd 2019_Kwangwoon_Univ_CE_DS_Project_1/
```

## How to build and run?

```
make
./run ShootForLog.txt property(>=1664)
```

examples)

If owner of a club gives you 350 billion won ...

```
./run ShootForLog.txt 3500
```

If owner of a club gives you 450 billion won ...

```
./run ShootForLog.txt 4500
```

## How can I check whether my code is correct?

Compare the results below

[./run ShootForLog.txt 2000](https://drive.google.com/open?id=14TlG9f7jf4DjTmlojxDXEp1EDXJlvUN0)

[./run ShootForLog.txt 2500](https://drive.google.com/open?id=1zGfh0J4CmHlMjB9_7r_iUVEotpM8Atit)

[./run ShootForLog.txt 3000](https://drive.google.com/open?id=1E7hVWB99bOvFMMh_HFuneuN-4_SIjjRD)

[./run ShootForLog.txt 3500](https://drive.google.com/open?id=1uoEowSn5nknaj3L29WIKF_Z755RekeTU)

[./run ShootForLog.txt 4000](https://drive.google.com/open?id=1jwVK9DeDDWuUO-vqI8G1frMLcDRaLQa9)

[./run ShootForLog.txt 4500](https://drive.google.com/open?id=1Cj2A9pDCZSOAAx_duqm1SswsHLSA-Ymm)

[./run ShootForLog.txt 5000](https://drive.google.com/open?id=1wlRD2TtoJrX4RgVn0KdEyJpmJnd8pR9Q)
