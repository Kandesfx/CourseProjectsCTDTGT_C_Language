#include "CheckingFunction.h"

int isEmpty_lcp(CampaignSList lcp)
{
	if (lcp.head == NULL)
	{
		return 1; //Nếu danh sách rỗng
	}
	else
	{
		return 0; //Nếu danh sách không rỗng
	}
}
int isEmpty_lvt(VolunteerSList lvt)
{
	if (lvt.head == NULL)
	{
		return 1; //Nếu danh sách rỗng
	}
	else
	{
		return 0; //Nếu danh sách không rỗng
	}
}
int checkSDT(VolunteerSList lvt, Volunteer vt)
{
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next) //Duyệt danh sách
	{
		if (strcmp(p->info.SDT, vt.SDT) == 0)
		{
			return 1; //Tồn tại số điện thoại trùng với đầu vào
		}
	}
	return 0; //Không tồn tại
}
int checkMaTNV(VolunteerSList lvt, Volunteer vt)
{
	for (VolunteerSNode* p = lvt.head; p != NULL; p = p->next) //Duyệt danh sách
	{
		if (strcmp(p->info.maTNV, vt.maTNV) == 0)
		{
			return 1;//Tồn tại mã tình nguyên viên trùng với mã tình nguyện viên đầu vào
		}
	}
	return 0; //Không tồn tại mã tình nguyện viên
}
int checkMaCP(CampaignSList lcp, Volunteer vt)
{
	for (CampaignSNode* p = lcp.head; p != NULL; p = p->next) //Duyệt danh sách
	{
		if (strcmp(p->info.maCD, vt.MaCD) == 0)
		{
			return 1; //Tồn tại mã chiến dịch trùng với mã chiến dịch đầu vào
		}
	}
	return 0; //Không tồn tại mã chiến dịch đầu vào
}
int checkSDTFormat(char* SDT)
{
	if (strlen(SDT) != 10) 
		return 0; //Số điện thoại có độ dài không đúng
	for (int i = 0; SDT[i] != '\0'; i++) {
		if (SDT[i] < '0' || SDT[i] > '9')
			return 0; //Số điện thoại chứa các ký tự khác số
	}
	return 1; //Số điện thoại hợp lệ
}
int checkBrtDayFormat(char* BrtDay)
{
	if (strlen(BrtDay) != 10)
		return 0;

	// Kiểm tra các ký tự ngăn cách
	if (BrtDay[2] != '/' || BrtDay[5] != '/')
		return 0;

	// Kiểm tra các ký tự ngày, tháng, năm
	for (int i = 0; i < 10; i++) {
		if (i == 2 || i == 5)
			continue; // Bỏ qua dấu "/"
		if (BrtDay[i] < '0' || BrtDay[i] > '9')
			return 0; // Nếu không phải số, không đúng định dạng
	}
	int day, month, year;
	//Lấy thông tin thời gian hiện tại
	struct tm localTime;
	time_t now = time(NULL);
	localtime_s(&localTime, &now);
	int validYear = (localTime.tm_year + 1900) - 14;
	//Đọc định thời gian
	sscanf_s(BrtDay, "%d/%d/%d", &day, &month, &year);
	// Kiểm tra ngày
	if (day < 1 || day > 31)
		return 0;

	// Kiểm tra tháng
	if (month < 1 || month > 12)
		return 0;

	// Kiểm tra năm
	if (year < 1900 || year > validYear)
		return 0;

	// Kiểm tra các tháng có số ngày hợp lệ
	int daysInMonth;
	switch (month) {
	case 4: case 6: case 9: case 11:
		daysInMonth = 30;
		break;
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			daysInMonth = 29; // Năm nhuận
		else
			daysInMonth = 28;
		break;
	default:
		daysInMonth = 31;
	}

	if (day > daysInMonth)
		return 0;
	return 1; //Ngày nhập vào là đúng định dạng
}