#include<iostream>
#include <cstdlib>
#include <pthread.h>
#include<bits/stdc++.h>
  
using namespace std;

volatile bool hasInput(false);

char inputDir;

void ClearScreen()
{
	system("clear");
	//std::cout << "\033[2J\033[H";
}
pair<int,int> wrong(-1,-1);
pair<int,int> NextCoordinates(char dir, pair<int,int> &current, int n, int m)
{
	pair<int,int> pr(current.first, current.second);
	switch(dir)
	{
		case 'E':
		{
			if(pr.first + 1 == m) return wrong;
			pr.first += 1;
		}
		break;
		case 'S':
		{
			if(pr.second + 1 == n) return wrong;
			pr.second += 1;
		}
		break;
		case 'W':
		{
			if(pr.first == 0) return wrong;
			pr.first -= 1;
		}
		break;
		case 'N':
		{
			if(pr.second == 0) return wrong;
			pr.second -= 1;
		}
		break;
	}
	return pr;
}

const void Draw(const vector<vector<int> > &grid, bool end = false)
{
	if(end)
	{
		cout<<"Game Ended"<<endl;
		return;
	}
	for(int j=0;j<grid[0].size();j++)
	{
		cout<<"_";
	}
	for(int i= 0 ;i < grid.size(); i++)
	{
		cout<<"|"<<endl;
		for(int j=0;j<grid[0].size();j++)
		{
			if(grid[i][j] == 1) cout<<"#";
			else if(grid[i][j] == 2) cout<<"@";
			else if(grid[i][j] == -1) cout<<"*";
			else cout<<" ";
		}
		cout<<"|"<<endl;
	}
	for(int j=0;j<grid[0].size();j++)
	{
		cout<<"_";
	}
}

char ChangeDirection(char dir, char input)
{
	switch(input)
	{
		case 'w':
		case 'W':
		{
			if(dir == 'S') return dir;
			return 'N';
		}
		break;
		case 'd':
		case 'D':
		{
			if(dir == 'W') return dir;
			return 'E';
		}
		break;
		case 's':
		case 'S':
		{
			if(dir == 'N') return dir;
			return 'S';
		}
		break;
		case 'a':
		case 'A':
		{
			if(dir == 'E') return dir;
			return 'W';
		}
		break;
	}
}

void* getInput(void*) {
    while (true) {
		//usleep(500);
		cin>>inputDir;
        //std::getline(std::cin, input);  // This blocks until the user enters input
        hasInput = true;  // Set flag to true when input is available
    }
}

int main()
{
	std::srand(std::time(NULL));
	pthread_t inputThread;  // Thread for handling input
    pthread_create(&inputThread, 0, getInput, 0);  // Start the input thread
	vector<vector<int> > grid(30, vector<int>(50,0));
	vector<pair<int,int> > snakePath(20, wrong);
	snakePath[0].first = 0;
	snakePath[0].second = 0;
	int snakeLen = 8;
	snakePath[19] = wrong;
	char dir = 'E';
	char input = 'E';
	while(true)
	{
		usleep(80000);
		ClearScreen();
		
		if (hasInput) 
		{
			hasInput = false;
			dir = ChangeDirection(dir,inputDir);
			
			while(true)
			{
				bool valid = true;
				int randomNumber1 = std::rand() % grid.size();
				int randomNumber2 = std::rand() % grid.size();
				pair<int,int> pr(randomNumber1,randomNumber2);
				for(int i=0;i<20;i++)
				{
					if(pr == snakePath[i])
					{
						valid = false;
					}
				}
				if(valid)
				{
					grid[pr.second][pr.first] = -1;
					break;
				}
			}
			
		}
		
		pair<int,int> next = NextCoordinates(dir, snakePath[0], grid.size(),grid[0].size());
		if(next.first == -1)
		{
			Draw(grid, true);
			break;
		}
		if(snakePath[19].first != -1)
			grid[snakePath[19].second][snakePath[19].first] = 0;
		
		for(int i=19;i>0;i--)
		{
			snakePath[i] = snakePath[i-1];
		}
		snakePath[0] = next;
		//cout<<"Next: "<<next.first<<"|"<<next.second<<endl;
		
		grid[snakePath[0].second][snakePath[0].first] = 2;
		
		for(int i=1;i<snakeLen;i++)
		{
			grid[snakePath[i].second][snakePath[i].first] = 1;
		}
		
		for(int i=snakeLen;i<20;i++)
		{
			if(snakePath[i].first != -1)
			grid[snakePath[i].second][snakePath[i].first] = 0;
		}
	
		Draw(grid);
	}
	
	pthread_join(inputThread, 0);
}