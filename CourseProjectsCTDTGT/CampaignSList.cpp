#include "CampaignSList.h"
#include "CheckingFunction.h"

void InitCampaignSList(CampaignSList& lcp)
{
	lcp.head = NULL; //Khởi tạo con trỏ đầu rỗng
	lcp.tail = NULL; //Khởi tạo con trỏ cuối rỗng 
}
CampaignSNode* CreateCampaignSNode(Campaign x)
{
	CampaignSNode* node = new CampaignSNode; //Cấp phát vùng nhớ động cho con trỏ node
	if (node == NULL)
	{
		printf("Khong du bo nho cap phat\n");
		return NULL;
	}
	node->info = x;
	node->next = NULL;
	return node; //Trả về con trỏ nút vừa khởi tạo
}
int insertTail_lcp(CampaignSList& lcp, CampaignSNode* p)
{
	if (p == NULL)
	{
		return 0; //Thực hiện không thành công
	}
	if (isEmpty_lcp(lcp) == 1)
	{
		lcp.head = p;
		lcp.tail = p;
	}
	else
	{
		lcp.tail->next = p;
		lcp.tail = p;
	}
	return 1; //Thực hiện thành công

}
void showCampaignSNode(CampaignSNode* p)
{
	printf_s("%-15s%-27s%-15s%-15s\n", p->info.maCD, p->info.tenCD, p->info.ngayBD, p->info.ngayKT);
}
void showCampaignSList(CampaignSList lcp)
{
	if (isEmpty_lcp(lcp) == 1)
	{
		printf("Danh sach rong!\n");
		return;
	}
	printf_s("%-15s%-27s%-15s%-15s\n", "Ma chien dich", "Ten chien dich", "Ngay bat dau", "Ngay ket thuc");
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next)
	{
		showCampaignSNode(p);
	}
}