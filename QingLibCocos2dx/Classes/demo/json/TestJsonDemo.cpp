//
//  TestJsonDemo.cpp
//  QingLibCocos2dx
//
//  Created by Kevin Geng on 14-9-29.
//
//

#include "TestJsonDemo.h"
#include "libjson.h"

USING_NS_QING;

bool TestJsonDemo::init()
{
	bool bRet = false;
	do
	{
	    m_bTouchEnabled = false;
        m_bAccelerometerEnabled = false;
		bRet = true;
	}while(0);
	return bRet;
}

TestJsonDemo::TestJsonDemo()
{
    
}

TestJsonDemo::~TestJsonDemo()
{
    
}

CCLayer* TestJsonDemo::getLayerByIndex()
{
	CCLayer * layer = CCLayer::create();

	switch (m_nLayerIndex) {
        case 0:{
            setTitle("JSON_NODE test");
            
            JSONNODE *n = json_new(JSON_NODE);
            json_push_back(n, json_new_i("test_num", 100) );
            json_push_back(n, json_new_a("test_str", "Kevin"));
            json_push_back(n, json_new_a("test_chinese", "中国"));
            json_char *jc = json_write_formatted(n);
            string str = jc;
            json_free(jc);
            json_delete(n);
            
            string json = "{\"number\":88,\"string\":\"oneRain\",\"charactor\":\"汉字\"}";
            JSONNODE *node = json_parse(json.c_str());
            JSONNODE_ITERATOR i = json_begin(node);
            json_char * node_name       = NULL;
            json_char * node_valude_str = NULL;
            json_int_t  node_value_int  = 0;
            json_number node_value_num  = 0;
            json_bool_t node_value_bool = 0;
            while(i != json_end(node))
            {
                if(*i != NULL) {
                    node_name = json_name(*i);
                    switch(json_type(*i)) {
                        case JSON_NULL:
                            break;
                        case JSON_STRING:
                            node_valude_str = json_as_string(*i);
                            json_free(node_valude_str);
                            break;
                        case JSON_NUMBER:
                            node_value_int = json_as_int(*i);
                            node_value_num = json_as_float(*i);
                            if(node_value_int != node_value_num) {
//                                ret->set(node_name, node_value_num);
                            } else if(node_value_int > 0){
//                                ret->set(node_name, (unsigned int)node_value_int);
                            } else {
//                                ret->set(node_name, (int)node_value_int);
                            }
                            break;
                        case JSON_BOOL:
                            node_value_bool = json_as_bool(*i);
//                            ret->set(node_name, (node_value_bool == 0) ? false : true);
                            break;
                        case JSON_ARRAY:
                        {
//                            Object data = decode(*i);
//                            ret->set(node_name, data);
//                            data->release();
                            break;
                        }
                        case JSON_NODE:
                        {
//                            Object data = decode(*i);
//                            ret->set(node_name, data);
//                            data->release();
                            break;
                        }
                        default:
                            throw "Error!";
                            break;
                    }
                    
                    CCLOG("node_name=%s, type=%d, value=%s", node_name, json_type(*i), node_valude_str);
                    json_free(node_name);  
                }
                ++i;
            }
            
            
            createLabel(layer, str);
        }
            break;
            
		default:
            break;
    }
            
	
	return layer;
}

