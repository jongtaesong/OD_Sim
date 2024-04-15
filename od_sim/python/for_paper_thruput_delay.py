# -*- coding: utf-8 -*-
"""
Created on Thu May 25 10:28:41 2023

@author: user
"""

import string
import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import scipy.stats

import matplotlib.pyplot
from matplotlib import gridspec
from subprocess import call
import os




def FILE_TO_ARRAY(filename):
    f = open(filename,'r')
    string=f.read()
    f.close()
    return string.split('\n')

def Parse_data(STR):
    Temp=STR.split(',')
    dummy=Temp[0].split('from ')
    A=dummy[1].split(' to ')
    a=int(A[0])
    b=int(A[1])

    dummy=Temp[1].split('delay = ')
    B=dummy[1].split(' at timeslot ')
    c=int(B[0])
    d=int(B[1])
    return a,b,c,d

def MAKE_number_ARRAY(DATA):
    A=[]
    B=[]
    C=[]
    D=[]
    for dat in DATA:
        if dat=='':
            break
        a,b,c,d=Parse_data(dat)
        A.append(a)
        B.append(b)
        C.append(c)
        D.append(d)
    return A,B,C,D

def column(matrix, i):
    return [row[i] for row in matrix]

def mean_confidence_interval(data, confidence=0.95):
    a = 1.0*np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    h = se * sp.stats.t._ppf((1+confidence)/2., n-1)
    return m, m-h, m+h


def make_5d_array (i_,j_,k_,l_,m_):
    result =[[[[[0 for m in range(m_)] \
                 for l in range(l_)] \
                 for k in range(k_)] \
                 for j in range(j_)] \
                 for i in range(i_)]
    return result

def make_2d_array (i_,j_):
    result =[[0 for j in range(j_)]for i in range(i_)] 
    return result


def extract_simticks (data):

   a = data.split('    ')
   print (' >> data = ', data, '\n >> a = ', a)
   i=0
   while a[i] == '':
       i = i+1
       print (' >> a = ', a, 'i', i)
   return a[i]


def find_index(text, data):
    for i in range(len(data)):
        if data[i] == text:
            return i
    print ('Error Cannot find ', text, 'in ', data)
    return 999


def find_plot_larger_than(val, x_list, y_list, mk):
    size = 0 
    for i in range(len(x_list)):
        if y_list[i] > val:
            size = size+1
    x_list_new = [0 for l in range(size)]
    y_list_new = [0 for l in range(size)]
    j = 0
    for i in range(len(x_list)):
        if y_list[i] > val:
            x_list_new[j] = x_list[i]
            y_list_new[j] = y_list[i]
            j = j+1
    return x_list_new, y_list_new


test_return_check = ['0','1'] # 0: Not Check, 1: Check
test_load = ['100']#['20','30','40','50','60','70','80','90','100']
test_window_size = ['32','128', '100000'] # window size 100000 --> no window control
test_priority = ['0', '1','2'] # 0: highest, 2: lowest
test_app_id = ['0', '1','2'] # cpu
test_mem_bw = [ '60','100','140','180','220','260','300','340','380', \
               '420','460','500','540','580','620','660','700','740','780']
test_mem_bw_f = [0 for p in range(len(test_mem_bw))]
for z in range(len(test_mem_bw)):
    test_mem_bw_f[z] = float(test_mem_bw[z])/100
    


s_m=len(test_window_size)
s_l=len(test_mem_bw)
s_k=len(test_load)
s_j=len(test_app_id) 
s_i=len(test_return_check)
print(f'test_window_size: {test_window_size}')
print(f'test_mem_bw: {test_mem_bw}')
print(f'test_load: {test_load}')
print(f'test_app_id: {test_app_id}')
print(f'test_return_check: {test_return_check}')
 
result_num_packets = make_5d_array (s_i, s_j, s_k, s_l, s_m)
result_avg_delay1  = make_5d_array (s_i, s_j, s_k, s_l, s_m)
result_avg_delay2  = make_5d_array (s_i, s_j, s_k, s_l, s_m)
result_avg_delay3  = make_5d_array (s_i, s_j, s_k, s_l, s_m)

result_file_name = '../output_file/Sim_Result_Summary.txt'
print(result_file_name)


DATA = FILE_TO_ARRAY(result_file_name)
for z in range(len(DATA)):
    temp1 = DATA[z].split(' ')
    if temp1[0] == 'clks/us':
        #print (temp1)
        clk_usec = int(temp1[1])
    if temp1[0] == 'app_id:':
        #print (temp1)

        i = find_index(temp1[9], test_return_check)
        j = find_index(temp1[1], test_app_id)
        k = find_index(temp1[5], test_load)
        l = find_index(temp1[11], test_mem_bw)
        m = find_index(temp1[7], test_window_size)
        
        if i+j+k+l+m < 999:
            result_num_packets[i][j][k][l][m] = temp1[25]
            result_avg_delay1[i][j][k][l][m] = int(temp1[19])/int(temp1[25])/clk_usec #convert from clocks to usecs
            result_avg_delay2[i][j][k][l][m] = int(temp1[21])/int(temp1[25])/clk_usec
            result_avg_delay3[i][j][k][l][m] = int(temp1[23])/int(temp1[25])/clk_usec



num_pkt_per_membw_app = make_2d_array(s_j, s_l)
delay2_per_membw_app = make_2d_array(s_j, s_l)
delay1_per_membw_app = make_2d_array(s_j, s_l)

for k in range(len(test_load)):
    for i in range(len(test_return_check)):
        for m in range(len(test_window_size)):                
            for j in range(len(test_app_id)):                
                for l in range(len(test_mem_bw)):
                    num_pkt_per_membw_app[j][l] = int(result_num_packets[i][j][k][l][m])

                if test_app_id[j] =='0':
                    p00 = plt.plot(test_mem_bw_f, num_pkt_per_membw_app[j][:], marker='v', label='check', markersize=10)
                elif test_app_id[j] =='1':
                    p01 = plt.plot(test_mem_bw_f, num_pkt_per_membw_app[j][:], marker='o', label='check', markersize=10)
                elif test_app_id[j] =='2':
                    p02 = plt.plot(test_mem_bw_f, num_pkt_per_membw_app[j][:], marker='D', label='check', markersize=10)

               
            plt.ylabel('Num Pkts', fontsize=20)
            plt.xlabel('Mem BW (x 100Gbps)', fontsize=20)
            plt.rc('xtick', labelsize=14)
            plt.rc('ytick', labelsize=14)
            plt.legend((p00[0], p01[0], p02[0]), ('priority 0', 'priority 1', 'priority 2'), loc=(0.65,0.1), fontsize=14)
            #plt.ylim([-10, 1000]) 
            plt.title('resp check:'+test_return_check[i]+' window:'+test_window_size[m], fontsize=20)
            plt.show()






for k in range(len(test_load)):
    for m in range(len(test_window_size)):                
        for i in range(len(test_return_check)):
            for j in range(len(test_app_id)):                
                for l in range(len(test_mem_bw)):
                    #delay2_per_membw_app[j][l]  = result_avg_delay2[i][j][k][l][m]
                    delay1_per_membw_app[j][l]  = result_avg_delay1[i][j][k][l][m]                                   
                    delay2_per_membw_app[j][l]  = result_avg_delay2[i][j][k][l][m]                                   
                                               
            
            #p0 = plt.plot(test_window_size, delay1_per_win_check,  marker='v', label='check')
            #p1 = plt.plot(test_window_size, delay1_per_win_uncheck,  marker='o', label='unckeck')
                
                if test_return_check[i] == '0':
                    if test_app_id[j] =='0':
                        #p20 = plt.plot(test_mem_bw_f, delay2_per_membw_app[j][:], marker='v', label='check')
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'v')
                        p20 = plt.plot(x_list, y_list, marker='v', linestyle=':', label='check', markersize=10)
                        
                    elif test_app_id[j] =='1':
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'o')
                        p21 = plt.plot(x_list, y_list, marker='o', linestyle=':', label='check', markersize=10)
                        #print x_list, y_list
                        #p21 = plt.plot(test_mem_bw_f, delay2_per_membw_app[j][:], marker='o', label='check')
                    elif test_app_id[j] =='2':
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'o')
                        p22 = plt.plot(x_list, y_list, marker='D', linestyle=':', label='check', markersize=10)
                
                
                if test_return_check[i] == '1':
                    if test_app_id[j] == '0':
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'v')
                        #print (f'p30......x:{x_list} ,y:{y_list}')
                        p30 = plt.plot(x_list, y_list, marker='v', label='check', markersize=10)
                    elif test_app_id[j] == '1':
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'o')
                        p31 = plt.plot(x_list, y_list, marker='o', label='check', markersize=10)
                        #print (f'p31......x:{x_list} ,y:{y_list}')
                    elif test_app_id[j] == '2':
                        x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'o')
                        p32 = plt.plot(x_list, y_list, marker='D', label='check', markersize=10)
                        #print (f'p32......x:{x_list} ,y:{y_list}')
                
        plt.ylabel('Delay (usec)', fontsize=20)
        plt.xlabel('Mem BW (x 100Gbps)', fontsize=20)
        plt.rc('xtick', labelsize=14)  
        plt.rc('ytick', labelsize=14)
        #plt.ylim([0, 9.5]) 
        plt.ylabel('Delay (usec)', fontsize=15)
        plt.xlabel('Mem BW (x 100Gbps)', fontsize=15) 
        plt.legend((p20[0], p30[0], p21[0], p31[0], p22[0], p32[0]), \
                   ('p0 PS_FC','p0 PS_RQ_FC', 'p1 PS_FC ', 'p1 PS_RQ_FC', 'p2 PS_FC', 'p2 PS_RQ_FC'), \
                   loc=(0.55,0.35), fontsize=14)
        plt.title('window:'+test_window_size[m], fontsize=20)
        plt.show()

for k in range(len(test_load)):
    for m in range(len(test_window_size)):                
        for j in range(len(test_app_id)):                
            for i in range(len(test_return_check)):
                for l in range(len(test_mem_bw)):
                    delay1_per_membw_app[j][l]  = result_avg_delay1[i][j][k][l][m]                                   
                    delay2_per_membw_app[j][l]  = result_avg_delay2[i][j][k][l][m]                                   
                if test_return_check[i] =='0':
                    x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'v')
                    p40 = plt.plot(x_list, y_list, marker='v', label='check', markersize=10)
                    
                elif test_return_check[i] =='1':
                    x_list, y_list = find_plot_larger_than(0.1, test_mem_bw_f, delay2_per_membw_app[j][:],'o')
                    p41 = plt.plot(x_list, y_list, marker='D', label='check', markersize=10)

            plt.xlim([-0.1, 5.1]) 
            plt.ylabel('Delay (usec)', fontsize=15)
            plt.xlabel('Mem BW (x 100Gbps)', fontsize=15) 
            
            plt.legend((p40[0], p41[0]), ('PS_FC', 'PS_RQ_FC'), loc=(0.6,0.7), fontsize=14)
            plt.title('priority:'+test_app_id[j]+' window:'+test_window_size[m], fontsize=20)
            plt.show()


