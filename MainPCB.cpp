#include"Scheduler.h"
#include"ID_Manager.h"
#include"ProcessManagement.h"
#include"plikiFAT.h"
#include<iostream>
ProcessManagement mng;
int main(){

	mng.CreateProcess("aaa", "a", 1);
	mng.CreateProcess("bbb", "a", 2);
	//mng.CreateProcess("ccc", "a");
	//mng.CreateProcess("Bambosz ty wuju", "a", 5);
	//mng.CreateProcess("ddd", "a", 1);
	mng.DisplayScheduler();

		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();		
		mng.Run();
		mng.DisplayScheduler();		
		std::cout << std::endl << "sleep" << std::endl;
		mng.Sleep(2);
		mng.Run();
		mng.DisplayScheduler();		
		mng.Run();


		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();

		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		std::cout << std::endl << "wakeUp" << std::endl;
		mng.WakeUp(1);
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();
		mng.Run();
		mng.DisplayScheduler();

	return 0;
}
