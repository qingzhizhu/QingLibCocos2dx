package com.qingzhizhu.ext;

public enum TestEnum { 
    Mon(1), Tue(2), Wed(3), Thu(4), Fri(5), Sat(6), Sun(7); 

    private int index; 

    TestEnum(int idx) { 
        this.index = idx; 
    } 

    public int getIndex() { 
        return index; 
    } 
 } 