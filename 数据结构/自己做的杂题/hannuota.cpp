#include <bits/stdc++.h>

void hannuota(int n,char Start,char Asist,char End)
{
	if(n == 1)
	{
		std::cout<< "move " << Start << " to " << End << "\n";
		return;
	}
	hannuota(n - 1,Start,End,Asist);
	std::cout<< "move " << Start << " to " << End << "\n";
	hannuota(n - 1,Asist,Start,End);

}
int main()
{
	int n;
	std::cin>> n;
	hannuota(n,'1','2','3');
	return 0;
}