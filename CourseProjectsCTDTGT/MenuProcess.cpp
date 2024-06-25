#include "Function.h"
void Continute_ClrScreen()
{
	printf_s("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Nhan phim bat ki de tiep tuc<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	_getch();
	system("cls"); //Lệnh làm sạch màn hình
}
void ShowMenu()
{
	printf_s("\n*************************************************************************");
	printf_s("\n*                                  Menu                                 *");
	printf_s("\n*-----------------------------------------------------------------------*");
	printf_s("\n* 0.  Thoat chuong trinh                                                *");
	printf_s("\n* 1.  Doc du lieu tu file chien dich(2)                                 *");
	printf_s("\n* 2.  Doc du lieu tu file tinh nguyen vien(2)                           *");
	printf_s("\n* 3.  In ra man hinh danh sach chien dich                               *");
	printf_s("\n* 4.  In ra man hinh danh sach tinh nguyen vien                         *");
	printf_s("\n* 5.  Them tinh nguyen vien moi(3)                                      *");
	printf_s("\n* 6.  Tim kiem tinh nguyen vien theo cac tieu chi(4)                    *");
	printf_s("\n* 7.  In ra toan bo tinh nguyen vien sap xep theo ten chien dich(5)     *");
	printf_s("\n* 8.  Tim thong tin cac tinh nguyen vien co tuoi nho nhat(6)            *");
	printf_s("\n* 9.  Tim kiem tinh nguyen vien tham gia cac chien dich co thoi gian    *");
	printf_s("\n*      dien ra nhieu ngay nhat (7)                                      *");
	printf_s("\n* 10.  Sap xep danh sach tinh nguyen vien theo ma chien dich(8)         *");
	printf_s("\n* 11.  In ra man hinh thong tin cac tinh nguyen vien co tuoi < 20(9)    *");
	printf_s("\n* 12. Tim kiem va cap nhat thong tin tinh nguyen vien(10)               *");
	printf_s("\n*************************************************************************");
}
void process()
{
	int luachon, result, prmCP = 0, prmVT = 0;
	CampaignSList LCP;
	VolunteerSList LVT;
	InitCampaignSList(LCP); //Khởi tạo danh sách chiến dịch rỗng
	InitVolunteerSList(LVT); //Khởi tạo danh sách tình nguyện viên rỗng
	do
	{
		ShowMenu();
		printf_s("\n Moi ban chon mot chuc nang: ");
		scanf_s("%d", &luachon);
		switch (luachon)
		{
		case 0:
			printf_s("\Ban da thoat khoi chuong trinh!");
			break;
		case 1:
			if (prmCP == 0) //Nếu chỉ số bằng 0 có nghĩa chương trình chưa từng đọc file
			{
				prmCP = inputCampaignList_LoadFile(LCP);
				if (prmCP == 1)
				{
					printf_s("\nDoc du lieu tu file thanh cong!");
				}
			}
			else //Nếu chỉ số bằng 1 thì file đã được đọc từ trước, không đọc thêm nữa
			{
				printf_s("\nDoc khong thanh cong! File da duoc doc du lieu tu truoc!");
			}
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 2:
			if (prmVT == 0) //Nếu chỉ số bằng 0 có nghĩa chương trình chưa từng đọc file
			{
				prmVT = inputVolunteerList_LoadFile(LCP, LVT);
				if (prmVT == 1)
				{
					printf_s("\nDoc du lieu tu file thanh cong!");
				}
			}
			else //Nếu chỉ số bằng 1 thì file đã được đọc từ trước, không đọc thêm nữa
			{
				printf_s("\nDoc khong thanh cong! File da duoc doc du lieu tu truoc!");
			}
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 3:
			showCampaignSList(LCP);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 4:
			showVolunteerSList(LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 5:
			if (addVolunteer(LVT, LCP) == 1)
			{
				printf_s("\nThem tinh nguyen vien thanh cong!");
			}
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 6:
			searchVolunteer(LCP, LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 7:
			showFullVolunteerByCP(LCP, LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 8:
			showVolunteerMinAge(LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 9:
			findVolunteersMostday(LCP, LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 10:
			sortVolunteers_ByNameCP(LCP, LVT);
			showVolunteerSList(LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 11:
			VolunteersSortAgeDecreaseName(LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		case 12:
			updateVLTandWriteLog(LCP, LVT);
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		default:
			printf_s("\nLua chon cua ban khong hop le! Moi nhap lai!");
			Continute_ClrScreen(); //Làm sạch màn hình
			break;
		}
	} while (luachon != 0);
}
int main()
{
	process();
	_getch();
}