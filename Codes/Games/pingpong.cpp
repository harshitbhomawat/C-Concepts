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
	pthread_t inputThread;  // Thread for handling input
    pthread_create(&inputThread, 0, getInput, 0);  // Start the input thread
	vector<vector<int> > grid(50, vector<int>(50,0));
	
	while(true)
	{
		usleep(80000);
		ClearScreen();
		
		if (hasInput) 
		{
			hasInput = false;
			dir = ChangeDirection(dir,inputDir);
			//cout<<"Dir Changed to "<<dir<<endl;
			//break;
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