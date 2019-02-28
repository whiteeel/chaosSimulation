#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(){
	//FILE* lyap = fopen("lyap", "wt");
	//FILE* xy;
	//3つの星の座標点を記録するファイル
	FILE* xy0 = fopen("xy0", "wt");
	FILE* xy1 = fopen("xy1", "wt");
	FILE* xy2 = fopen("xy2", "wt");

	double G = 1.4;  //重力定数
	int N = 3;		 //星の数
	float M = 1.0;   //星の質量　変えなくてもよい

	double pi = 3.14159265359;  //円周率
	int i, j, k, l;
	double kaku;
	double r, fx, fy;
	double t, dt;

	//char filename[50000];

	double x[3], y[3];
	double v_x[3], v_y[3];
	double f_x[3], f_y[3];

	float teisu_u[2], teisu_k[2];
	teisu_k[0] = 0.5;
	teisu_k[1] = 0.5;
	teisu_u[0] = 0.0;
	teisu_u[1] = 1.0;

	for (i = 0; i < N; i++){
		kaku = 2.0*pi*i / N;
		v_x[i] = -sin(kaku);
		v_y[i] = cos(kaku);
		x[i] = cos(kaku);
		y[i] = sin(kaku);
	}

	fprintf(xy0, "%f  %f\n", x[0], y[0]);
	fprintf(xy1, "%f  %f\n", x[1], y[1]);
	fprintf(xy2, "%f  %f\n", x[2], y[2]);

	t = 0.0;
	dt = 1.0 / 300.0;

	for (i = 0; i < 300000; i++){
		t = t + dt;
		for (k = 0; k < 2; k++){
			for (j = 0; j < N; j++){
				f_x[j] = 0.0;
				f_y[j] = 0.0;
			}
			for (l = 0; l < N; l++){
				for (j = l + 1; j < N; j++){
					r = sqrt((x[l] - x[j])*(x[l] - x[j]) + (y[l] - y[j])*(y[l] - y[j]));
					fx = -G*M*M*(x[l] - x[j]) / (r*r*r);
					fy = -G*M*M*(y[l] - y[j]) / (r*r*r);
					f_x[l] = f_x[l] + fx;
					f_y[l] = f_y[l] + fy;
					f_x[j] = f_x[j] - fx;
					f_y[j] = f_y[j] - fy;
				}
			}

			for (j = 0; j < N; j++){
				v_x[j] = v_x[j] + dt*teisu_u[k] * f_x[j] / M;
				v_y[j] = v_y[j] + dt*teisu_u[k] * f_y[j] / M;
			}
			for (j = 0; j < N; j++){
				x[j] = x[j] + dt*teisu_k[k] * v_x[j];
				y[j] = y[j] + dt*teisu_k[k] * v_y[j];
			}

			fprintf(xy0, "%f  %f\n", x[0], y[0]);
			fprintf(xy1, "%f  %f\n", x[1], y[1]);
			fprintf(xy2, "%f  %f\n", x[2], y[2]);

			//sprintf(filename, "%d", i);
			//xy = fopen(filename, "w");
			//fprintf(xy, "%f  %f\n", x[0], y[0]);
			//fprintf(xy, "%f  %f\n", x[1], y[1]);
			//fprintf(xy, "%f  %f\n", x[2], y[2]);
			//fclose(xy);
		}
	}
	fclose(xy0);
	fclose(xy1);
	fclose(xy2);
}