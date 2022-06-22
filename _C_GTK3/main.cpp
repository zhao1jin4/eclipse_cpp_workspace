#include "main.h"

//	const int *A 或  int const *A; //const修饰指向的对象，A可变，A指向的对象不可变

//	int *const A;            //const修饰指针A，     A不可变，A指向的对象可变
//
//	const int *const A;      //指针A和A指向的对象都不可变

int main(int  argc, char* argv[])
{
	//return gtk3_button_box::main(argc,argv);
	//return gtk2_hello::main(argc,argv);//GKT3 OK
	//return gtk2_hello2::main(argc,argv);//GKT3 OK
	//----------------//GKT3 OK
//	int param_argc=2;
//	char * parm_argv[2];
//	parm_argv[0]="box";
//	parm_argv[1]="1";
//	return gtk2_box::main(param_argc,parm_argv);//不能链接fprintf
	//----------------
	//return gtk2_container::main(argc,argv);//GKT3 OK
	//return gtk2_button_icon::main(argc,argv);//GKT3 OK
	//return gtk2_button_radio::main(argc,argv);//GKT3 OK

	//return gtk2_complex_one::main(argc,argv);

	//return gtk2_label::main(argc,argv);//GKT3 OK
	//return gtk2_arrow::main(argc,argv);//GKT3 OK

	//return gtk2_progress_bar::main(argc,argv);//很多编译错误,enum 不能 做|操作 ??
	//return gtk2_rule::main(argc,argv);
	//return gtk2_status_bar::main(argc,argv);//GKT3 OK
	//return gtk2_entry_text::main(argc,argv);
	//return gtk2_spin_button::main(argc,argv);
	//return gtk2_calendar::main(argc,argv);
	//return gtk2_color_selection::main(argc,argv);
	//return gtk2_file_selection::main(argc,argv);

	//return gtk2_event_box::main(argc,argv);//GKT3 OK
	//return gtk2_fixed::main(argc,argv);//GKT3 OK
	//return gtk2_frame::main(argc,argv);//GKT3 OK
	//return gtk2_aspect_frame::main(argc,argv);//GKT3 OK
	//return gtk2_paned::main(argc,argv);//GKT3 OK

	//return gtk2_scrolled_window::main(argc,argv);

	return gtk2_button_box::main(argc,argv);//GKT3 OK

	//return gtk2_toolbar::main(argc,argv);
	//return gtk2_notebook::main(argc,argv);

	//return gtk2_menu::main(argc,argv);//GKT3 OK


	//return gtk2_complex_two::main(argc,argv);
	//return gtk2_selection::main(argc,argv);
	//return gtk2_selection_two::main(argc,argv);
	//return gtk2_game::main(argc,argv);//编译错误

}
