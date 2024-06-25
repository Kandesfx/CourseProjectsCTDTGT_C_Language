#ifndef _CampaignSList_h
#define _CampaignSList_h

#include <stdio.h>

struct Campaign
{
	char maCD[11]; //Mã chiến dịch
	char tenCD[25]; //Tên chiến dịch
	char ngayBD[25]; //Ngày bắt đầu chiến dịch
	char ngayKT[25]; //Ngày kết thúc chiến dịch
};
struct CampaignSNode
{
	Campaign info; //Thông tin của nút
	CampaignSNode* next; //Con trỏ chỉ đến nút kế sau
};
struct CampaignSList
{
	CampaignSNode* head; //Con trỏ đầu
	CampaignSNode* tail; //Con trỏ cuối
};

void InitCampaignSList(CampaignSList& lcp); //Khởi tạo danh sách rỗng
CampaignSNode* CreateCampaignSNode(Campaign x); //Khởi tạo nút mới
int insertTail_lcp(CampaignSList& lcp, CampaignSNode* p); //Thêm một phần tử vào cuối danh sách
void showCampaignSNode(CampaignSNode* p); //Hiển thị thông tin 1 nút
void showCampaignSList(CampaignSList lcp); //Hiển thị thông tin danh sách

#endif _CampaignSList_h

