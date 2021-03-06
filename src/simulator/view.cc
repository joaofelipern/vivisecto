#include "view.h"

void view_xScale(Mat *view, int SIM_DIM_X, int SIM_DIM_Y){ *view = Mat(SIM_DIM_X*scale, 300 + SIM_DIM_Y*scale, CV_8UC4); }

void view_drawNodes(Mat *view, Node* model_node[], int node_count){ 

	for(int i=0;i<node_count;i++){

		circle( *view, Point( model_node[i]->x * scale, model_node[i]->y * scale), 15, Scalar(0,255,255), -1,8,0);
		char node_id_str[3];
		sprintf(node_id_str,"%d",i);

		if(i > 9 && i < 100)
			putText( *view,node_id_str, Point(-11 + model_node[i]->x * scale, 6 + model_node[i]->y * scale), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(10,10,10), 2,8,false );

		else if(i > 99)
			putText( *view,node_id_str, Point(-11 + model_node[i]->x * scale, 6 + model_node[i]->y * scale), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(10,10,10), 2,8,false );

		else
			putText( *view,node_id_str, Point(-6 + model_node[i]->x * scale, 6 + model_node[i]->y * scale), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(10,10,10), 2,8,false );

	}

}

void view_drawRadioComm(Mat *view, Node* model_node[], int node_count){

	for(int i=0;i<node_count;i++){

		if(model_node[i]->ev_type == 2){
			circle( *view, Point( (model_node[i]->x) * scale, (model_node[i]->y) * scale), 23, Scalar(20,255,20), -1,8,0);
			line(*view, Point(model_node[i]->x * scale,model_node[i]->y * scale),
				 	Point(model_node[model_node[i]->sender]->x*scale,model_node[model_node[i]->sender]->y*scale),Scalar(0,255,0), 2,8,0);
		}// if ends here

		// Transmitting node
		else if(model_node[i]->ev_type == 1)
			circle( *view, Point( (model_node[i]->x) * scale, (model_node[i]->y) * scale), 21, Scalar(255,191,0), -1,8,0);

	}// end of FOR

}

void view_drawStats(Mat *view, Node* model_node[], int node_count, double sim_t){

	// draw simulation time on top right corner of screen
	char sim_t_str[15];
	sprintf(sim_t_str,"%lf",sim_t);	
	putText( *view,sim_t_str, Point(view->cols - 120,30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255,255,255), 2,8,false );
	
	int total_pkts_tx = 0;
	int total_pkts_rx = 0;

	for(int i=0;i<node_count;i++){
		total_pkts_tx += model_node[i]->pkts_tx;
		total_pkts_rx += model_node[i]->pkts_rx;
	}

	char stat_str[30] = "STAT";
	putText( *view,stat_str, Point(view->cols - 250,110), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
	sprintf(stat_str,"TX : %5d packets",total_pkts_tx);
	putText( *view,stat_str, Point(view->cols - 250,140), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
	sprintf(stat_str,"RX : %5d packets",total_pkts_rx);
	putText( *view,stat_str, Point(view->cols - 250,160), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

}

void view_drawModel(Mat *view, Node* model_node[], int node_count,int batch_idx){

	char node_i_str[50] = "MODEL";
	putText( *view,node_i_str, Point(view->cols - 250,200), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

	strcpy(node_i_str,"id      x   y  pkt_tx pkt_rx");
	putText( *view,node_i_str, Point(view->cols - 250,230), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );

	
	if(batch_idx == -1){
		for(int i=0;i<node_count;i++){
			sprintf(node_i_str,"N%03d %3d %3d %4d %4d",i,model_node[i]->x,model_node[i]->y,model_node[i]->pkts_tx,model_node[i]->pkts_rx);
			putText( *view,node_i_str, Point(view->cols - 250,240 + ((i+1) * 20) ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
		}
	}
	else{
		int j=0;
		for(int i=batch_idx; i < batch_idx + 10 && i < node_count;i++){
			sprintf(node_i_str,"N%03d %3d %3d %4d %4d",i,model_node[i]->x,model_node[i]->y,model_node[i]->pkts_tx,model_node[i]->pkts_rx);
			putText( *view,node_i_str, Point(view->cols - 250,240 + ((j+1) * 20) ), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255), 2,8,false );
			j++;
		}
	
	}


}


