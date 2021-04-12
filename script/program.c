#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

FILE *F_EIGENVAL, *F_KPOINTS;
int trash_int,ISPIN,total_grid,NBANDS,path_grid,path_number;
//path_number=경로의수.
//path_grid=한경로가몇개로쪼개져있는지.
//total_grid=총경로가몇개로쪼개져있는지.
double fermi_E,trash_double,bandgap=0;
//fermi_E= 페르미에너지값을저장합니다.
//bandgap=밴드갭값을계산해서저장합니다.
char EIGENVAL[10]="EIGENVAL";
char KPOINTS[10]="KPOINTS";
char path_name[150][5];
char trash_char[100];
int NEDOS;
double fermi_E_dos;

void grep_fermi_E();
void grep_EIGENVAL_data();
void grep_KPOINTS_data();
void make_EIGENVAL_data();
void write_gnuplot();
void implement();
void grep_DOSCAR_data();
void write_DOSCAR_data();

int main(int argc, char *argv[]){

  int i;
  printf("=================================================================\n");
  printf("what do you want ?\n");
  printf("1 => bandstructure\n");
  printf("2 => DOS,PDOS\n");
  printf("=================================================================\n");

  scanf("%d",&i);
  
  if(i==1){//1번을선택시bandstructure을그립니다.
    
  grep_fermi_E();//fermi energy 값을입력.
  
  grep_EIGENVAL_data();//EIGENVAL파일에서필요한 데이터를입력.
  
  grep_KPOINTS_data();//KPOINTS파일에서필요한 데이터를입력.

  path_number=total_grid/path_grid;

  make_EIGENVAL_data();//EIGENVAL에서 데이터를 가져와 txt파일을만듬.
  
  write_gnuplot();
 
  implement();// 밴드그리는것을 수행합니다.
  }
  else if(i==2){
    grep_DOSCAR_data();
    write_DOSCAR_data();
    
  }
  return 0;
}

void grep_DOSCAR_data(){

  FILE *F_DOSCAR;
  int check,i;
  
  F_DOSCAR=fopen("DOSCAR","r");
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  for(i=0;i<2;i++)
    check=fscanf(F_DOSCAR,"%lf",&trash_double);
  check=fscanf(F_DOSCAR,"%d",&NEDOS);
  check=fscanf(F_DOSCAR,"%lf",&fermi_E_dos);
  fclose(F_DOSCAR);
}

void write_DOSCAR_data(){

  FILE *F_DOSCAR;
  FILE *w_data[10];
  int i,j,k=0,l,check=1;
  double data[10][NEDOS+1][10];
  
  F_DOSCAR=fopen("DOSCAR","r");
  for(i=1;i<=6;i++)fgets(trash_char,sizeof(trash_char),F_DOSCAR);
  //토탈도스부분을0번에저장합니다.
  for(i=1;i<=NEDOS;i++){
    for(j=1;j<=3;j++){
      check =fscanf(F_DOSCAR,"%lf",&data[k][i][j]);     
    }
  }

  k++;
  for(i=1;i<=2;i++)
  fgets(trash_char,sizeof(trash_char),F_DOSCAR);

  while(1){
    for(i=1;i<=NEDOS;i++){
      for(j=1;j<=4;j++){
	check =fscanf(F_DOSCAR,"%lf",&data[k][i][j]);     
      }
    }
    k++;
    for(i=1;i<=2;i++)
    fgets(trash_char,sizeof(trash_char),F_DOSCAR);
    if(check==EOF)break;
  }
  
  
  l=4; //뽑고싶은번호를써줍니다.
  sprintf(trash_char,"w_%d.txt",l);
  w_data[l]=fopen(trash_char,"w");
  for(i=1;i<=NEDOS;i++){
    //fprintf(w_data[l],"%f %f\n",data[l][i][1],data[l][i][2]);
    //fprintf(w_data[l],"%f %f\n",data[l][i][1],data[l][i][3]);
    //fprintf(w_data[l],"%f %f\n",data[l][i][1],data[l][i][4]);
    fprintf(w_data[l],"%f %f %f %f\n",data[l][i][1],data[l][i][2],data[l][i][3],data[l][i][4]);
  }
  fclose(w_data[l]);
  fclose(F_DOSCAR);
}


void grep_fermi_E(){
  printf("=================================================================\n");
  printf("Please write Fermi energy.\n");
  printf("=================================================================\n");
  scanf("%lf",&fermi_E);
}

void grep_EIGENVAL_data(){

  int i;
  
  F_EIGENVAL=fopen(EIGENVAL,"r");
  
  for(i=0;i<3;i++)fscanf(F_EIGENVAL,"%d",&trash_int);
  fscanf(F_EIGENVAL,"%d",&ISPIN);
  for(i=0;i<6;i++)fscanf(F_EIGENVAL,"%lf",&trash_double);
  for(i=0;i<2;i++)fscanf(F_EIGENVAL,"%s",trash_char);
  fscanf(F_EIGENVAL,"%d",&trash_int);
  fscanf(F_EIGENVAL,"%d",&total_grid);
  fscanf(F_EIGENVAL,"%d",&NBANDS);
  fclose(F_EIGENVAL);
  
 
}

void grep_KPOINTS_data(){
  
  int check,i,count=0;
  
  F_KPOINTS=fopen(KPOINTS,"r");
  fgets(trash_char,sizeof(trash_char),F_KPOINTS);
  check=fscanf(F_KPOINTS,"%d",&path_grid);
  fgets(trash_char,sizeof(trash_char),F_KPOINTS);
  fgets(trash_char,sizeof(trash_char),F_KPOINTS);
  fgets(trash_char,sizeof(trash_char),F_KPOINTS);
  while(1){
    count++;

    for(i=0;i<3;i++)check=fscanf(F_KPOINTS,"%lf",&trash_double);
    check=fscanf(F_KPOINTS,"%s",trash_char); //포인트이름앞에데이터들을버립니다. 

    check=fscanf(F_KPOINTS,"%s",path_name[count]);//포인트이름을1,2,3..순서로저장합니다.
    
    if(check==EOF)break;
  }
  
  fclose(F_KPOINTS);
}
void make_EIGENVAL_data(){
  
  FILE *w_a[NBANDS+1];
  FILE *w_b[NBANDS+1];
  FILE *min_a_file[NBANDS+1];
  FILE *min_b_file[NBANDS+1];
  int i,j,k,l,count_w_path=0,count_minus_a=0,count_minus_b=0;
  //count_minus = 음수인맥시멈포인트의수를셉니다.
  double min_a[NBANDS+1];
  double min_b[NBANDS+1];
  //conduction,valence 상관없이페르미에너지에가까운값을저장합니다.
  double min_a_E=100000,max_a_E=100000;
  double min_b_E=100000,max_b_E=100000;
  //min_a or b_E = a,b는eigenval파일에서세로첫번쨰줄이냐두번쨰줄이냐를의미합니다.각각 의최소최댜값을찾는것입니다.
  double E_EIGENVAL;
  double graph_x=0;
  double point_x[total_grid+1],point_y[total_grid+1],point_z[total_grid+1];
  //k공간에서x,y,z를저장하는공간입니다.
  double min_point_a_x[NBANDS+1],min_point_a_y[NBANDS+1],min_point_a_z[NBANDS+1];
  double min_point_b_x[NBANDS+1],min_point_b_y[NBANDS+1],min_point_b_z[NBANDS+1];
  
  F_EIGENVAL=fopen(EIGENVAL,"r");
  
  for(i=0;i<6;i++)fgets(trash_char,sizeof(trash_char),F_EIGENVAL);
  for(i=1;i<=total_grid;i++){     
    fscanf(F_EIGENVAL,"%lf %lf %lf %lf",&point_x[i],&point_y[i],&point_z[i],&trash_double);
    if(i!=1){
      graph_x+=sqrt((point_x[i]-point_x[i-1])*(point_x[i]-point_x[i-1])+(point_y[i]-point_y[i-1])*(point_y[i]-point_y[i-1])+(point_z[i]-point_z[i-1])*(point_z[i]-point_z[i-1]));
    }
    if(i==1){//i==1일때비교할최소값이없으므로임의로10만이라는큰값을써주어 비교하게합니다.
      if(ISPIN==1){
	for(k=1;k<=NBANDS;k++){
	  min_a[k] = 100000;	  
	}
      }
      else if(ISPIN==2){
	for(k=1;k<=NBANDS;k++){
	  min_a[k] = 100000;
	  min_b[k] = 100000;
	}
      }
    }
    if(ISPIN==1){
      
      for(j=1;j<=2*NBANDS;j++){//j는하나의패스에서각각밴드의에너지를스캔하는것입니다.
	fscanf(F_EIGENVAL,"%lf",&E_EIGENVAL); count_w_path=0;//패스네임을쓰기위한정수입니다.
	for(k=1;k<=NBANDS;k++){
	  if(j==2*k){
	    for(l=0;l<path_number;l++){
	      if(i==path_grid*l+1){
		sprintf(trash_char,"w_a%d.txt",k);
		w_a[k]=fopen(trash_char,"a+");
		if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		  min_a[k]=E_EIGENVAL-fermi_E;
		  min_point_a_x[k] = point_x[i];
		  min_point_a_y[k] = point_y[i];
		  min_point_a_z[k] = point_z[i];

		  sprintf(trash_char,"min_a_file%d.txt",k);
		  min_a_file[k]=fopen(trash_char,"w");
		  fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		  fclose(min_a_file[k]);
		}
		fprintf(w_a[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+1]);
		fclose(w_a[k]);
		count_w_path++;
		break;
	      }
	      else if(i==path_grid*(l+1)){
		sprintf(trash_char,"w_a%d.txt",k);
		w_a[k]=fopen(trash_char,"a+");
		if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		 min_a[k]=E_EIGENVAL-fermi_E;
		 min_point_a_x[k] = point_x[i];   
		 min_point_a_y[k] = point_y[i];
		 min_point_a_z[k] = point_z[i];

		 sprintf(trash_char,"min_a_file%d.txt",k);
		 min_a_file[k]=fopen(trash_char,"w");
		 fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		 fclose(min_a_file[k]);
		}
		fprintf(w_a[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+2]);
		fclose(w_a[k]);
		count_w_path++;
		break;
	      }
	    }
	    if(count_w_path==0){
	      sprintf(trash_char,"w_a%d.txt",k);
	      w_a[k]=fopen(trash_char,"a+");
	      if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		min_a[k]=E_EIGENVAL-fermi_E;
		min_point_a_x[k] = point_x[i];   
		min_point_a_y[k] = point_y[i];
		min_point_a_z[k] = point_z[i];

		sprintf(trash_char,"min_a_file%d.txt",k);
		min_a_file[k]=fopen(trash_char,"w");
		fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		fclose(min_a_file[k]);
	      }
	      fprintf(w_a[k],"%f %f\n",graph_x,E_EIGENVAL);
	      fclose(w_a[k]);
	    }
	  }
	}
      }
    }
    
  
    if(ISPIN==2){
      
      for(j=1;j<=3*NBANDS;j++){
	fscanf(F_EIGENVAL,"%lf",&E_EIGENVAL);count_w_path=0;
	for(k=1;k<=NBANDS;k++){
	  if(j==3*k-1){
	    for(l=0;l<=path_number;l++){
	      if(i==path_grid*l+1){
		sprintf(trash_char,"w_a%d.txt",k);
		w_a[k]=fopen(trash_char,"a+");
		if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		  min_a[k]=E_EIGENVAL-fermi_E;
		  min_point_a_x[k] = point_x[i];   
		  min_point_a_y[k] = point_y[i];
		  min_point_a_z[k] = point_z[i];

		  sprintf(trash_char,"min_a_file%d.txt",k);
		  min_a_file[k]=fopen(trash_char,"w");
		  fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		  fclose(min_a_file[k]);
		}
		fprintf(w_a[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+1]);
		fclose(w_a[k]);
		count_w_path++;
		break;
	      }
	      else if(i==path_grid*(l+1)){
		sprintf(trash_char,"w_a%d.txt",k);
		w_a[k]=fopen(trash_char,"a+");
		if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		  min_a[k]=E_EIGENVAL-fermi_E;
		  min_point_a_x[k] = point_x[i];   
		  min_point_a_y[k] = point_y[i];
		  min_point_a_z[k] = point_z[i];

		  sprintf(trash_char,"min_a_file%d.txt",k);
		  min_a_file[k]=fopen(trash_char,"w");
		  fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		  fclose(min_a_file[k]);
		}
		fprintf(w_a[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+2]);
		fclose(w_a[k]);
		count_w_path++;
		break;
	      }
	    }
	    if(count_w_path==0){
	      sprintf(trash_char,"w_a%d.txt",k);
	      w_a[k]=fopen(trash_char,"a+");
	      if(fabs(min_a[k])>fabs(E_EIGENVAL-fermi_E)){
		min_a[k]=E_EIGENVAL-fermi_E;
		min_point_a_x[k] = point_x[i];   
		min_point_a_y[k] = point_y[i];
		min_point_a_z[k] = point_z[i];

		sprintf(trash_char,"min_a_file%d.txt",k);
		min_a_file[k]=fopen(trash_char,"w");
		fprintf(min_a_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		fclose(min_a_file[k]);
	      }
	      fprintf(w_a[k],"%f %f\n",graph_x,E_EIGENVAL);
	      fclose(w_a[k]);
	    }
	  }
	  else if(j==3*k){
	    for(l=0;l<=path_number;l++){
	      if(i==path_grid*l+1){
		sprintf(trash_char,"w_b%d.txt",k);
		w_b[k]=fopen(trash_char,"a+");
		if(fabs(min_b[k])>fabs(E_EIGENVAL-fermi_E)){
		  min_b[k]=E_EIGENVAL-fermi_E;
		  min_point_b_x[k] = point_x[i];   
		  min_point_b_y[k] = point_y[i];
		  min_point_b_z[k] = point_z[i];
		  
		  sprintf(trash_char,"min_b_file%d.txt",k);
		  min_b_file[k]=fopen(trash_char,"w");
		  fprintf(min_b_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		  fclose(min_b_file[k]);
		}
		fprintf(w_b[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+1]);
		fclose(w_b[k]);
		count_w_path++;
		break;
	      }
	      else if(i==path_grid*(l+1)){
		sprintf(trash_char,"w_b%d.txt",k);
		w_b[k]=fopen(trash_char,"a+");
		if(fabs(min_b[k])>fabs(E_EIGENVAL-fermi_E)){
		  min_b[k]=E_EIGENVAL-fermi_E;
		  min_point_b_x[k] = point_x[i];   
		  min_point_b_y[k] = point_y[i];
		  min_point_b_z[k] = point_z[i];

		  sprintf(trash_char,"min_b_file%d.txt",k);
		  min_b_file[k]=fopen(trash_char,"w");
		  fprintf(min_b_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		  fclose(min_b_file[k]);
		}
		fprintf(w_b[k],"%f %f %s\n",graph_x,E_EIGENVAL,path_name[2*l+2]);
		fclose(w_b[k]);
		count_w_path++;
		break;
	      }
	    }
	    if(count_w_path==0){
	      sprintf(trash_char,"w_b%d.txt",k);
	      w_a[k]=fopen(trash_char,"a+");
	      if(fabs(min_b[k])>fabs(E_EIGENVAL-fermi_E)){
		min_b[k]=E_EIGENVAL-fermi_E;
		min_point_b_x[k] = point_x[i];   
		min_point_b_y[k] = point_y[i];
		min_point_b_z[k] = point_z[i];
		
		sprintf(trash_char,"min_b_file%d.txt",k);
		min_b_file[k]=fopen(trash_char,"w");
		fprintf(min_b_file[k],"%f %f\n",graph_x,E_EIGENVAL);
		fclose(min_b_file[k]);
	      }
	      fprintf(w_b[k],"%f %f\n",graph_x,E_EIGENVAL);
	      fclose(w_b[k]);
	    }
	  }
	}
      }
    }
  }
  //Bandgap 을출력하기위한계산부분입니다.
  if(ISPIN==1){
    printf("=================================================================\n");
    for(k=1;k<=NBANDS;k++){
      printf("min_a[%d] = %6f      >>>>",k,min_a[k]);
      printf("min_point_x,y,z = %f %f %f\n",min_point_a_x[k],min_point_a_y[k],min_point_a_z[k]);
      if(min_a[k]<=0){count_minus_a++;}
    }
    printf("=================================================================\n");
    bandgap = min_a[count_minus_a+1]-min_a[count_minus_a];
    printf("Band Gap = %f\n",bandgap);
    printf("=================================================================\n");
  }
  else if(ISPIN==2){
    printf("=================================================================\n");
    for(k=1;k<=NBANDS;k++){
      printf("min_a[%d] = %6f      >>>>",k,min_a[k]);
      printf("min_point_x,y,z = %f %f %f\n",min_point_a_x[k],min_point_a_y[k],min_point_a_z[k]);
      printf("min_b[%d] = %6f      >>>>",k,min_b[k]);
      printf("min_point_x,y,z = %f %f %f\n",min_point_b_x[k],min_point_b_y[k],min_point_b_z[k]);
      if(min_a[k]<=0)count_minus_a++;
      if(min_b[k]<=0)count_minus_b++;
    }
    printf("=================================================================\n");
    for(l=1;l<=count_minus_a;l++){
      if(fabs(max_a_E)>fabs(min_a[l]))max_a_E=min_a[l];  
    }
    for(l=count_minus_a+1;l<=NBANDS;l++){
      if(fabs(min_a_E)>fabs(min_a[l]))min_a_E=min_a[l]; 
    }
    for(l=1;l<=count_minus_b;l++){
      if(fabs(max_b_E)>fabs(min_b[l]))max_b_E=min_b[l]; 
    }
    for(l=count_minus_b+1;l<=NBANDS;l++){
      if(fabs(min_b_E)>fabs(min_b[l]))min_b_E=min_b[l]; 
    }

    if(min_a_E<min_b_E)bandgap += min_a_E;
    else bandgap += min_b_E;
    if(max_a_E>max_b_E)bandgap -= max_a_E;
    else bandgap -= max_b_E;
    printf("Band Gap = %f\n",bandgap);
    printf("=================================================================\n");


    //파일에써지는EIGENVAL값은모두실제값을바로써준것입니다.(페르미에너지보정안했음.)
  }
}


void write_gnuplot(){

  FILE *F_gnuplot;
  int i,j,k;
  int resolution1,resolution2;
  double y_range1,y_range2;
  
  F_gnuplot=fopen("g.g","w");
  
  fprintf(F_gnuplot,"set term gif size ");

  // 그래프해상도조절하고싶다면이것을수정할것.
  resolution1 = 700; resolution2 = 1200;
  // 그래프의y범위를수정하고싶다면..
  y_range1 = -10 ; y_range2 = 10;
  
  fprintf(F_gnuplot,"%d,%d ",resolution1,resolution2);
  
  fprintf(F_gnuplot,"enhanced\n");
  fprintf(F_gnuplot,"set output 'band.gif'\n");
  fprintf(F_gnuplot,"set yrange[%f:%f]\n",y_range1,y_range2);
  fprintf(F_gnuplot,"unset key\n");
  fprintf(F_gnuplot,"\n");
  fprintf(F_gnuplot,"plot");
  for(j=1;j<=NBANDS;j++){
    fprintf(F_gnuplot,"'w_a%d.txt' u 1:($2+%f):xtic(3) w l lc -1,",j,-fermi_E);
    fprintf(F_gnuplot,"\\");
    fprintf(F_gnuplot,"\n");
    if(ISPIN==2){
      fprintf(F_gnuplot,"'w_b%d.txt' u 1:($2+%f):xtic(3) w l lc -1,",j,-fermi_E);
      fprintf(F_gnuplot,"\\");
      fprintf(F_gnuplot,"\n");
    }
  }
  printf("Do you want draw minimum,maximum point?\n(1- yes 2- no)\n");
  printf("=================================================================\n");
  scanf("%d",&k);
  
  if(k==1){
    for(j=1;j<=NBANDS;j++){
      fprintf(F_gnuplot,"'min_a_file%d.txt' u 1:($2+%f):xtic(3) w p ps 1.5 pt 7 lc 7,",j,-fermi_E);
      fprintf(F_gnuplot,"\\");
      fprintf(F_gnuplot,"\n");
      if(ISPIN==2){
	fprintf(F_gnuplot,"'min_b_file%d.txt' u 1:($2+%f):xtic(3) w p ps 1.5 pt 7 lc 7,",j,-fermi_E);
	fprintf(F_gnuplot,"\\");
	fprintf(F_gnuplot,"\n");
      }
    }
  }
  fprintf(F_gnuplot,"0 w l lw 3 lc 7\n");
  
  fclose(F_gnuplot);
  
    
  
}
void implement(){
  
  system("gnuplot g.g");
  //system("rm g.g");
  //system("rm w_*.txt");
  //system("rm min_*.txt");
  system("display band.gif"); 
}  
