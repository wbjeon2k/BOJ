저는 updateDP(index, from, val) 함수를 애용합니다 (edited) 
DP[index]의 값이 val로 새로 update 되야 하는 상황이라면
RDP[index]에 from index를 저장해요
그러면, RDP만을 이용해서, 역추적이 가능하죠