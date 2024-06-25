#include "VolunteerSList.h"
#include "CheckingFunction.h"

void InitVolunteerSList(VolunteerSList& lvt)
{
	lvt.head = NULL; //Khởi tạo con trò đầu rỗng
	lvt.tail = NULL; //Khởi tạo con trỏ cuối rỗng 
}
VolunteerSNode* CreateVolunteerSNode(Volunteer x)
{
	VolunteerSNode* node = new VolunteerSNode;
	if (node == NULL)
	{
		printf("Khong du bo nho cap phat\n");
		return NULL; //Khởi tạo không thành công
	}
	node->info = x;
	node->next = NULL;
	return node; //Khởi tạo thành công
}
int insertTail_lvt(VolunteerSList& lvt, VolunteerSNode* p)
{
	if (p == NULL)
	{
		return 0; //Thực hiện không thành công
	}
	if (isEmpty_lvt(lvt) == 1)
	{
		lvt.head = p;
		lvt.tail = p;
	}
	else
	{
		lvt.tail->next = p;
		lvt.tail = p;
	}
	return 1; //Thực hiện thành công

}
void showVolunteerSNode(VolunteerSNode* p)
{
	printf_s("%-15s%-15s%-15s%-15s%-15s%-15s\n", p->info.maTNV, p->info.Ho, p->info.Ten, p->info.brtDay, p->info.SDT, p->info.MaCD);
}
void showVolunteerSList(VolunteerSList lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		printf("Danh sach tinh nguyen vien rong!\n");
		return;
	}
	printf_s("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Ma TNV", "Ho", "Ten", "Sinh ngay", "So dien thoai", "Ma chien dich");
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next)
	{
		showVolunteerSNode(p);
	}
}
int deleteVLTSList(VolunteerSList& lvt)
{
	if (isEmpty_lvt(lvt) == 1)
	{
		return 0; //Danh sách rỗng
	}
	while (lvt.head != NULL)
	{
		VolunteerSNode* p = lvt.head;
		lvt.head = lvt.head->next;
	}
	lvt.tail = NULL;
	return 1; //Xoá danh sách thành công
}