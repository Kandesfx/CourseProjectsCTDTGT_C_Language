#ifndef _VolunteerSList_h
#define _VolunteerSList_h

#include <stdio.h>

struct Volunteer
{
	char maTNV[15]; //Mã tình nguyện viên
	char Ho[25]; //Họ tình nguyên viên
	char Ten[11]; //Tên tình nguyên viên
	char brtDay[25]; //Ngày sinh tình nguyện viên
	char SDT[15]; //Số điện thoại tình nguyên viên
	char MaCD[11]; //Mã Chiến dịch tình nguyên viên tham gia
};
struct VolunteerSNode
{
	Volunteer info; //Thông tin của nút
	VolunteerSNode* next; //Con trỏ chỉ đến nút kế sau
};
struct VolunteerSList
{
	VolunteerSNode* head; //Con trỏ đầu
	VolunteerSNode* tail; //Con trỏ cuối
};

void InitVolunteerSList(VolunteerSList& lvt); //Khởi tạo danh sách rỗng 
VolunteerSNode* CreateVolunteerSNode(Volunteer x); //Khởi tạo nút mới
int insertTail_lvt(VolunteerSList& lvt, VolunteerSNode* p); //Thêm phần tử vào cuối danh sách
void showVolunteerSNode(VolunteerSNode* p); //Hiển thị thông tin 1 nút
void showVolunteerSList(VolunteerSList lvt); //Hiển thị thông tin danh sách
int deleteVLTSList(VolunteerSList& lvt); //Xoá Toàn bộ danh sách
#endif _VolunteerSList_h
