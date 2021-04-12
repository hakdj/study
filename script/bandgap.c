#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
 
 
  FILE *r,*rr,*rrr,*rrrr;
  int check,i,j,n,x=0,count=0,num=0;
  double a,k,d[1000],path=0,t=0;
  int c;
  char str[100],str1[100]={"EIGENVAL"},str2[100]={"KPOINTS"},b[1000],data[100];
 
    printf("페르미 에너지를 써주세요\n");
    scanf("%lf",&t);
  //printf("EIGENVAL 데이터가 존재하는 파일이름을 써주세요\n");
  //scanf("%s",str1);
  //printf("KPOINTS 데이터가 존재하는 파일이름을 써주세요\n");
  //scanf("%s",str2);
 
  r=fopen(str1,"r");
  rrrr=fopen(str2,"r");  
  rr=fopen("bandgap2.c","w");  
  rrr=fopen("g.g","w");
 
  while(1){
    check=fscanf(rrrr,"%s",str);
    if(*str=='!'){count++;}
    if(check==EOF)break;
  }
  path=(count-1)/2;
  fclose(rrrr);
 
  rrrr=fopen(str2,"r");
  fgets(data,sizeof(data),rrrr);
  check=fscanf(rrrr,"%lf",&d[0]);
 
  fgets(data,sizeof(data),rrrr);
  fgets(data,sizeof(data),rrrr);
  fgets(data,sizeof(data),rrrr);
 
  while(1){
    num++;
    check=fscanf(rrrr,"%lf",&d[num]);
    num++;
    check=fscanf(rrrr,"%lf",&d[num]);
    num++;
    check=fscanf(rrrr,"%lf",&d[num]);
    num++;
    check=fscanf(rrrr,"%s",&b[num]);
    num++;
    check=fscanf(rrrr,"%s",&b[num]);
  
    if(check==EOF)break;
  }
 
  fclose(rrrr);
 
 
 
  for(i=0;i<10;i++){
    check =fscanf(r,"%lf",&a);
  
  }
 
  fscanf(r,"%s",str);
  fscanf(r,"%s",str);
  fscanf(r,"%d",&n);
  fscanf(r,"%d",&n);
  fscanf(r,"%d",&n);
 
  fprintf(rr,"#include<stdio.h>\n#include<stdlib.h>\n#include<math.h>\nint main(int argc, char *argv[]){\nFILE *r;\nFILE *rr;\nFILE *rrrr;\n");
 
  for(j=1;j<=n;j++){
    fprintf(rr,"FILE *w%d;\n",j);
  }
  for(j=1;j<=n;j++){
    fprintf(rr,"FILE *w9%d;\n",j);
  }
 
    fprintf(rr,"double min[9%d];\n",j+1);
  
 
  for(j=1;j<=n;j++){
    fprintf(rr,"int e%d=1;\n",j);
    fprintf(rr,"int e9%d=1;\n",j);
  }
  fprintf(rr,"double tt=%f;\n",t);
  fprintf(rr,"int check,i,n,e=1,j,jj,f,x=0,y=0,count=0,path=0,num=0,t=0;\ndouble a,k,z=0,n2,n1=0,d[10000],check1;\nint c;\nchar str[100],str1[100],data[100],b[10000][10];\nr=fopen(\"%s\",\"r\");\nrr=fopen(\"%s\",\"r\");\n",str1,str2);
 
 
  fprintf(rr,"rrrr=fopen(\"%s\",\"r\");\nwhile(1){\ncheck=fscanf(rrrr,\"%%s\",str);\nif(*str=='!'){count++;}\nif(check==EOF)break;\n}\npath=(count-1)/2;\nfclose(rrrr);",str2);
 
 
  fprintf(rr,"\nrrrr=fopen(\"%s\",\"r\");\nfgets(data,sizeof(data),rrrr);\ncheck=fscanf(rrrr,\"%%lf\",&d[0]);\nfgets(data,sizeof(data),rrrr);\nfgets(data,sizeof(data),rrrr);\nfgets(data,sizeof(data),rrrr);\n\nwhile(1){\nnum++;\ncheck=fscanf(rrrr,\"%%lf\",&d[num]);\nnum++;\ncheck=fscanf(rrrr,\"%%lf\",&d[num]);\nnum++;\ncheck=fscanf(rrrr,\"%%lf\",&d[num]);\nnum++;\ncheck=fscanf(rrrr,\"%%s\",b[num]);\nnum++;\ncheck=fscanf(rrrr,\"%%s\",b[num]);\n\nif(check==EOF)break;\n}\n\nfclose(rrrr);\n",str2);
 
 
  for(j=1;j<=n;j++){
    fprintf(rr,"w%d=fopen(\"write%d.txt\",\"w\");\n",j,j);
  }
  for(j=1;j<=n;j++){
    fprintf(rr,"w9%d=fopen(\"write9%d.txt\",\"w\");\n",j,j);
  }
  fprintf(rr,"for(i=0;i<3;i++){\ncheck =fscanf(r,\"%%lf\",&a);}\ncheck =fscanf(r,\"%%d\",&t);\nfor(i=0;i<6;i++){\ncheck =fscanf(r,\"%%lf\",&a);\n}\nfscanf(r,\"%%s\",str);\nfscanf(r,\"%%s\",str);\nfscanf(r,\"%%d\",&n);\nfscanf(r,\"%%lf\",&n1);\nfscanf(r,\"%%d\",&n);\nn2=n1/path;\nwhile(1){\nx++;\ny++;\nfor(f=0;f<%f;f++){\nif(y>(%f*f+1)&&(y<=%f*(f+1))){\nz+=sqrt((d[5*2*f+1]-d[5*(2*f+1)+1])*(d[5*2*f+1]-d[5*(2*f+1)+1])+(d[5*2*f+2]-d[5*(2*f+1)+2])*(d[5*2*f+2]-d[5*(2*f+1)+2])+(d[5*2*f+3]-d[5*(2*f+1)+3])*(d[5*2*f+3]-d[5*(2*f+1)+3]))/(n2-1);}}\nfor(i=0;i<4;i++)\ncheck =fscanf(r,\"%%lf\",&a);\nif(check==EOF)break;\nif(t==1){\nfor(i=0;i<2*n;i++){\ncheck =fscanf(r,\"%%lf\",&a);\n",path,d[0],d[0]);
 
 
 
  fprintf(rr,"if(i==2*1-1){\nfor(j=0;j<=path;j++){\nif(x==30*j+1){\nfprintf(w1,\"%%f %%f %%s\\n\",z,a,b[10*j+5]);\nif(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;}}}\nelse if(x==30*j){\nfprintf(w1,\"%%f %%f %%s\\n\",z,a,b[10*j]);\nif(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;\n}\n}}\nelse{ fprintf(w1,\"%%f %%lf\\n\",z,a);\nif(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;\n}\n}\n}}}");
 
 
 
  for(j=2;j<=n;j++){
  
    fprintf(rr,"if(i==2*%d-1){\nfprintf(w%d,\"%%f %%lf\\n\",z,a);\nif(e%d==1){min[%d]=a-tt;e%d++;\n}else{ if(fabs(min[%d])>fabs(a-tt)){min[%d]=a-tt;\ne%d++;\n}\n}}",j,j,j,j,j,j,j,j);
  }
 
  fprintf(rr,"}}\n");
 
 
  fprintf(rr,"if(t==2){\nfor(i=0;i<3*n;i++){\ncheck =fscanf(r,\"%%lf\",&a);\n");

 
  fprintf(rr,"if(i==3*1-1){\nfor(j=0;j<=path;j++){\nif(x==30*j+1){\nfprintf(w1,\"%%f %%f %%s\\n\",z,a,b[10*j+5]);\n if(e91==1){min[91]=a-tt;e91++;\n}else{ if(fabs(min[91])>fabs(a-tt)){min[91]=a-tt;\ne91++;\n}\n}}\nelse if(x==30*j){\nfprintf(w91,\"%%f %%f %%s\\n\",z,a,b[10*j]); if(e91==1){min[91]=a-tt;e91++;\n}else{ if(fabs(min[91])>fabs(a-tt)){min[91]=a-tt;\ne91++;\n}\n}\n}\nelse fprintf(w91,\"%%f %%lf\\n\",z,a); if(e91==1){min[91]=a-tt;e91++;\n}else{ if(fabs(min[91])>fabs(a-tt)){min[91]=a-tt;\ne91++;\n}\n}\n}\n}");
 
 
  for(j=2;j<=n;j++){
  
    fprintf(rr,"if(i==3*%d-1){\n fprintf(w9%d,\"%%f %%lf\\n\",z,a);\nif(e9%d==1){min[9%d]=a-tt;e9%d++;\n}else{ if(fabs(min[9%d])>fabs(a-tt)){min[9%d]=a-tt;\ne9%d++;\n}\n}}",j,j,j,j,j,j,j,j);
  }
 
 
  fprintf(rr,"if(i==3*1-2){\nfor(j=0;j<=path;j++){\nif(x==30*j+1){\nfprintf(w1,\"%%f %%f %%s\\n\",z,a,b[10*j+5]);\n if(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;\n}\n}}\nelse if(x==30*j){\nfprintf(w1,\"%%f %%f %%s\\n\",z,a,b[10*j]); if(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;\n}\n}\n}\nelse fprintf(w1,\"%%f %%lf\\n\",z,a); if(e1==1){min[1]=a-tt;e1++;\n}else{ if(fabs(min[1])>fabs(a-tt)){min[1]=a-tt;\ne1++;\n}\n}\n}\n}");
 
 
 
  for(j=2;j<=n;j++){
  
    fprintf(rr,"if(i==3*%d-2){\n fprintf(w%d,\"%%f %%lf\\n\",z,a);if(e%d==1){min[%d]=a-tt;e%d++;\n}else{ if(fabs(min[%d])>fabs(a-tt)){min[%d]=a-tt;\ne%d++;\n}\n}\n}",j,j,j,j,j,j,j,j);
  }
 
 
 
  fprintf(rr,"}}}\n");
fprintf(rr,"if(t==1){\n");
 
 fprintf(rr,"for(jj=1;jj<=n-1;jj++){\nfor(j=1;j<=n-jj;j++){\nif(min[j]>min[j+1]){check1=min[j];min[j]=min[j+1];min[j+1]=check1;}\n}}\njj=1;\nfor(j=1;j<=n;j++){\nif(min[jj]>0)break;\nelse jj++; }\nprintf(\"bandgap = %%f\\n\",min[jj]-min[jj-1]);\n");

 for(j=1;j<=n;j++){
    fprintf(rr,"printf(\"min[%d]=%%f\\n\",min[%d]);\n",j,j);
    }
fprintf(rr,"}");

 
fprintf(rr,"if(t==2){\n");


 for(j=1;j<=n;j++){
fprintf(rr,"min[%d]=min[9%d];\n",26+j,j);
}
 
  fprintf(rr,"for(jj=1;jj<=2*n-1;jj++){\nfor(j=1;j<=2*n-jj;j++){\nif(min[j]>min[j+1]){check1=min[j];min[j]=min[j+1];min[j+1]=check1;}\n}}\njj=1;\nfor(j=1;j<=2*n;j++){\nif(min[jj]>0)break;\nelse jj++; }\nprintf(\"bandgap = %%f\\n\",min[jj]-min[jj-1]);\n");

   for(j=1;j<=2*n;j++){
    fprintf(rr,"printf(\"min[%d]=%%f\\n\",min[%d]);\n",j,j);
    }

fprintf(rr,"}");
 
  fprintf(rr,"fclose(r);\n");
  for(j=1;j<=n;j++){
    fprintf(rr,"fclose(w%d);\n",j);
  }
  for(j=1;j<=n;j++){
    fprintf(rr,"fclose(w9%d);\n",j);
  }
 
 
  fprintf(rrr,"set term gif size 600,1000 enhanced\nset output 'bandgap.gif'\nunset key\nset yrange [-7:7]\n\nplot");
 

  for(j=1;j<=n;j++){
    fprintf(rrr," 'write%d.txt' u 1:($2+%f):xtic(3) w l lc -1,",j,-t);
    fprintf(rrr,"\\");
    fprintf(rrr,"\n");
    fprintf(rrr," 'write9%d.txt' u 1:($2+%f):xtic(3) w l lc -1,",j,-t);
    fprintf(rrr,"\\");
    fprintf(rrr,"\n");
  }
  fprintf(rrr,"0 w l lw 3 lc 1\n");
 
  fprintf(rr,"system(\"gnuplot g.g\");\n");
  fprintf(rr,"return 0;\n}");
  fclose(rrr);fclose(rr);fclose(r);
 
  system("gcc -o bandgap2 bandgap2.c -lm");system("./bandgap2");
    system("rm bandgap2.c");
    system("rm g.g");
  system("rm bandgap2");
  system("rm write*.txt");
  system("display bandgap.gif");
 
  return 0;
}
