//
//
//  Project.c
//  Polyline_Editor
//
//  Created by vi on 15/11/17.
//  Copyright  year 2015 vi. All rights reserved.
//
//	zhoudong
//	1309853G-I011-0204
//
#include "C:\Users\student\Desktop\GLUT 3.7 for .NET/glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Point_Square    8       //enlarge the mouse click's range
#define MAX_Points      80      //max numbers for saving point
#define line_width      3       //drawing line width
#define MAX_SAVE        50      //max number for saving graphs that you draw

static GLint win_len = 800;     //windows length
static GLint win_wid = 500;    //winodws width

int record_p = 0;    //record the number of you click mouse, it would be use for begin function
int record_line = 1; //increase automatic by press keyboard 'b', it means lines number which is the set of point if you click would equal to record_line

int save_graph = 0;      //record how many number of graph that had been saved
int open_graph = 0;      //show which graph should be used now

char current_state = '0';       //record state that you press in keyboard
int fited_p[2] = {0,0};         //when you use 'found' function, it would record the index of point set (which point be found) if you found it exactly
GLint temp_point[2]={0,0};      //{x,y}°Arecord position that you left click mouse temporary
GLint point_set[MAX_SAVE][MAX_Points][MAX_Points][2];  //point set
int point_num[MAX_Points]; //how many points in each line

GLboolean click = GL_FALSE;         //whether you click left mouse
GLboolean found = GL_FALSE;         //whether find the point using 'find_p' function
GLboolean draw = GL_TRUE;           //whether you should refresh graph

//use for creating menu's name
char * ItoS (int n)
{
    int i,j,k=0,len;
    char *temp=(char *)malloc(n);
    char *result=(char *)malloc(n);
    i=0;
    do{
        temp[i++]=n%10+'0';
        
    }
    while ((n/=10)>0);
    temp[i]='\0';
    for(j=i;j>=0;j--,k++)
        result[k]=temp[j-1];
    result[i] = '\0';
    return result;
}

//begin function, draw ploylines
void Begin(){
    if(current_state != 'b'){
        return;
    }
    point_set[open_graph][record_line -1][record_p][0] = temp_point[0];
    point_set[open_graph][record_line -1][record_p][1] = temp_point[1];
    record_p++;
    point_num[record_line -1] = record_p;
    glutPostRedisplay();    //redraw
}

//for key b' operation
void key_b(){
    //when you click b and click left mouse before
    if(record_p != 0){
        record_p = 0;
        record_line ++;
    }
    current_state = 'b';
    draw = GL_TRUE;  
}

//this function is used to find point while user left click mouse
GLboolean find_p(){
    int i,j;
    for(i = 0; i < record_line; i++){
        for(j = 0; j < point_num[i]; j++){
            if(abs(temp_point[0] - point_set[open_graph][i][j][0]) < (Point_Square / 2) &&
               abs(temp_point[1] - point_set[open_graph][i][j][1]) < (Point_Square / 2) ){
                fited_p[0] = i;
                fited_p[1] = j;
                return GL_TRUE;
            }
        }
    }
    return GL_FALSE;
}

//for key d's operation
void key_d(){
    current_state = 'd';
    draw = GL_TRUE;   
}

//delete function
void Delete(){
    if(current_state != 'd'){
        return;
    }
    //set the current point to be (-1,-1)
    if(found == GL_TRUE){
        point_set[open_graph][fited_p[0]][fited_p[1]][0] = -1;
        point_set[open_graph][fited_p[0]][fited_p[1]][1] = -1;
    }
    glutPostRedisplay(); //redraw
    return;
}

//for key m's operation
void key_m(){
    current_state = 'm';
    draw = GL_TRUE;  
}

//move point function
void Move(int x, int y)
{
    if(current_state != 'm'){
        return;
    }
    //using the find point and change its position
    if(found == GL_TRUE && click == GL_TRUE) {
        point_set[open_graph][fited_p[0]][fited_p[1]][0] = x;
        point_set[open_graph][fited_p[0]][fited_p[1]][1] = win_wid - y;
    }
    glutPostRedisplay();    //redraw
}

//for key r's operation
void key_r(){
    draw = GL_FALSE;   
}

//for key i's operation
void key_i(){
    if(record_p != 0){
        record_p = 0;
        record_line ++;
    }
    current_state = 'i';
    draw = GL_TRUE;   
}

//insert function
void Insert(){
    if(current_state != 'i'){
        return;
    }
    if(record_p == 0 ){
        if(found != GL_TRUE)
            return;
        point_set[open_graph][record_line -1][0][0] = point_set[open_graph][fited_p[0]][fited_p[1]][0];
        point_set[open_graph][record_line -1][0][1] = point_set[open_graph][fited_p[0]][fited_p[1]][1];
    }
    else{
        point_set[open_graph][record_line -1][record_p][0] = temp_point[0];
        point_set[open_graph][record_line -1][record_p][1] = temp_point[1];
        
    }
    record_p++;
    point_num[record_line -1] = record_p; 
}

//clean the all polylines that you draw before
void key_c(){
    int i,j;
    for(i =0; i < record_line; i++){
        for(j = 0; j<point_num[i]; j++){
            point_set[open_graph][i][j][0] = -1;
            point_set[open_graph][i][j][1] = -1;
            
        }
    }
}

//dispay function
void display()
{
    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT);
    /* draw unit square polygon */
    //if you click r,°Adraw is GL_FALSE so it would not draw
    if(draw == GL_TRUE){
        int i,j;
        for(i =0; i < record_line; i++){
            glLineWidth(line_width) ;
            glBegin(GL_LINE_STRIP);
            for(j = 0; j<point_num[i]; j++){
                if(point_set[open_graph][i][j][0] >=0 && point_set[open_graph][i][j][1] >=0){
                    glVertex2i(point_set[open_graph][i][j][0], point_set[open_graph][i][j][1]);
                    glVertex2i(point_set[open_graph][i][j][0], point_set[open_graph][i][j][1]);
                }
            }
            glEnd();
        }
    }
    glFlush();
}

//key operation
void key(unsigned char key, int x, int y)
{
    switch (key) {
            //begin
        case 'b':
        case 'B':
            key_b();
            break;
            //delete
        case 'd':
        case 'D':
            key_d();
            break;
            //move
        case 'm':
        case 'M':
            key_m();
            break;
            //refresh
        case 'r':
        case 'R':
            key_r();
            glutPostRedisplay();
            break;
			//insert
        case 'i':
        case 'I':
            key_i();
            break;
			//clean, reset state 
        case 'c':
        case 'C':
            key_c();
			current_state = '0';
            glutPostRedisplay();
            break;
            //quit
        case 'q':
        case 'Q':
            current_state = 'q';
            exit(0);            //esc
    }
}

//for mouse click function. while using left click mouse, the follow function would done in this function
void get_point(int button, int state, int x, int y)
{  
    //check whether the point is in the point square
    if( (button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN) ) {
        if( x >Point_Square && (win_len-x) >Point_Square &&
           (y) >Point_Square && (win_wid-y) > Point_Square ) {
            //get the point
            temp_point[0] = x;
            temp_point[1] = win_wid - y;
            draw = GL_TRUE;
            switch (current_state) {
                case 'b':
                    Begin();
                    break;
                case 'm':
                    found = find_p();
                    click = GL_TRUE;
                    break;
                case 'd':
                    found = find_p();
                    Delete();
                    break;
                case 'i':
                    found = find_p();
                    Insert();
                    glutPostRedisplay();
                    break;
                default:
                    break;
            }
        }
        return;
    }
    //reset the state
    else if( (button==GLUT_LEFT_BUTTON) && (state==GLUT_UP) ) {
        click = GL_FALSE;
        found = GL_FALSE;
        return;
    }   
}

void init()
{
    /* set clear color to black */
    glClearColor (1.0, 1.0, 1.0, 0.0);
    /* set fill  color to white */
    glColor3f(0.0, 1.0, 1.0);
    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D(0, win_len, 0, win_wid);
}

//reshape the windows
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    /*  Reset viewport and projection parameters  */
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,  newWidth, 0.0, newHeight);
    
    /*  Reset display-window size parameters.  */
    win_len  = newWidth;
    win_wid = newHeight;
}

/************************
 menu setting
 ************************/
/**
 *  ID for menus:
 *  save is 1, open is 2,
 *  new is -1
 */
void Add_SaveMenu(){
    glutAddMenuEntry(ItoS(save_graph), save_graph);
    glutPostRedisplay();
}

void Add_OpenMenu(){
    glutAddMenuEntry(ItoS(save_graph), save_graph);
    glutPostRedisplay();
}

void for_save(int value){  
    //do new operation.
    if(value == -1){
        save_graph++;
        glutSetMenu(1);         //1 is the ID of save menu
        Add_SaveMenu();
        glutSetMenu(2);         //2 is the ID of open menu
        Add_OpenMenu();
        open_graph = save_graph;
    }
    //record polylines in  the menu established before
    else{
        int i,j;
        for(i =0; i< MAX_Points;i++){
            for(j=0; j<MAX_Points; j++){
                point_set[value-1][i][j][0] = point_set[open_graph][i][j][0];
                point_set[value-1][i][j][1] = point_set[open_graph][i][j][1];
            }
        }
        //beacuse all points record in the menu established before, so need to clean up all the record in the index open_graph of point_set
        for(i=0; i< MAX_Points;i++){
            for(j=0; j<MAX_Points; j++){
                point_set[open_graph][i][j][0] = 0;
                point_set[open_graph][i][j][1] = 0;
            }
        }
        open_graph = save_graph ;   //update open_graph      
    }
    current_state = '0';
    glutPostRedisplay();
}

//open polylines saved in menus
void for_open(int value){
    int i,j;
    for(i =0; i< MAX_Points;i++){
        for(j=0; j<MAX_Points; j++){
            point_set[open_graph][i][j][0] = point_set[value-1][i][j][0];
            point_set[open_graph][i][j][1] = point_set[value-1][i][j][1];
        }
    }
    current_state = '0';
    glutPostRedisplay();  
}

void root(int value){
    return;
}
//main function
int main(int argc, char** argv)
{
    
    int save, open;
    
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(win_len,win_wid);
    glutInitWindowPosition(100,100);
    glutCreateWindow("ZHOU_DONG");
    
    save = glutCreateMenu(for_save);        //save is 1
    glutAddMenuEntry("new", -1);
    
    open = glutCreateMenu(for_open);        //open is 2
    
    glutCreateMenu(root);
    glutAddSubMenu("save",save);
    glutAddSubMenu("open", open);   
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMouseFunc(get_point);
    glutKeyboardFunc(key); 
    glutMotionFunc(Move);
    glutDisplayFunc(display);
    glutReshapeFunc(winReshapeFcn);
    
    init();
    glutMainLoop();
    return 0;
}
