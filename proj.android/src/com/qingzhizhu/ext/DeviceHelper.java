package com.qingzhizhu.ext;

import com.qingzhizhu.cocos2dx.QingLibCocos2dx;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.text.TextUtils;



public class DeviceHelper {

//	http://blog.csdn.net/nanzhiwen666/article/details/8288433	
    /** 没有网络 */
    public static final int NETSTATUS_NONE = 0;
    /** 3G和3G以上网络，或统称为快速网络 */
    public static final int NETSTATUS_3G = 1;
    /** wifi网络 */
    public static final int NETSTATUS_WIFI = 2;
    /** 2G网络 */
    public static final int NETSTATUS_2G = 3;
    /** WAP网络 区分2G网络是为wap，还是net,类型，因为wap类型，需要配置代理上网 */
    public static final int NETSTATUS_2G_WAP = 4;

	
    public static boolean isWifiEnabled() {
		try {
			// requires ACCESS_WIFI_STATE
			WifiManager wm = (WifiManager) QingLibCocos2dx.getInstance().getSystemService(Context.WIFI_SERVICE);
			QingLibCocos2dx.log("[Device] wifi:" + wm.isWifiEnabled() + ";\t" + wm.toString()); 
			return wm.isWifiEnabled();
		} catch (Exception e) {
			QingLibCocos2dx.log("[Device] isWifiEnabled is fail, " + e.getMessage());
		}
		return false;
	}
    	
	
	/**
	 * 获取网络状态，wifi,wap,2g,3g.
	 *
	 * @param context 上下文
	 * @return int 网络状态 {@link #NETWORKTYPE_2G},{@link #NETWORKTYPE_3G},          *{@link #NETWORKTYPE_INVALID},{@link #NETWORKTYPE_WAP}* <p>{@link #NETWORKTYPE_WIFI}
	 */

	public static int getNetWorkType() {		
		ConnectivityManager manager = (ConnectivityManager) QingLibCocos2dx.getInstance().getSystemService(Context.CONNECTIVITY_SERVICE);		
		NetworkInfo networkInfo = manager.getActiveNetworkInfo();
		
		if (networkInfo != null && networkInfo.isConnected()) {
			QingLibCocos2dx.log("[Device]" + networkInfo.toString());
			String type = networkInfo.getTypeName();
			if (type.equalsIgnoreCase("WIFI")) {
				return NETSTATUS_WIFI;
            } else if (type.equalsIgnoreCase("MOBILE")) {
            	String proxyHost = android.net.Proxy.getDefaultHost();

            	return TextUtils.isEmpty(proxyHost)
            			? (isFastMobileNetwork(QingLibCocos2dx.getInstance()) ? NETSTATUS_3G : NETSTATUS_2G)
            			: NETSTATUS_2G_WAP;
            }
		}

		return NETSTATUS_NONE;
	} 


	/**
	 * 判断是否是FastMobileNetWork，将3G或者3G以上的网络称为快速网络
	 * @param context
	 * @return
	 */
	protected static boolean isFastMobileNetwork(Context context) {
		TelephonyManager telephonyManager = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
		QingLibCocos2dx.log("[device] country:" + telephonyManager.getSimCountryIso() + "\tSerialNum:" + telephonyManager.getSimSerialNumber());
		switch (telephonyManager.getNetworkType()) {		
			case TelephonyManager.NETWORK_TYPE_UNKNOWN:	//0
	            return false;
			case TelephonyManager.NETWORK_TYPE_GPRS:	//1
	            return false; // ~ 100 kbps
			case TelephonyManager.NETWORK_TYPE_EDGE:	//2
	            return false; // ~ 50-100 kbps
			case TelephonyManager.NETWORK_TYPE_UMTS:	//3
            return true; // ~ 400-7000 kbps
	        case TelephonyManager.NETWORK_TYPE_CDMA:	//4
	            return false; // ~ 14-64 kbps	        
	        case TelephonyManager.NETWORK_TYPE_EVDO_0:	//5
	            return true; // ~ 400-1000 kbps
	        case TelephonyManager.NETWORK_TYPE_EVDO_A:	//6
	            return true; // ~ 600-1400 kbps
	        case TelephonyManager.NETWORK_TYPE_1xRTT:	//7
	            return false; // ~ 50-100 kbps
	        case TelephonyManager.NETWORK_TYPE_HSDPA:	//8
	            return true; // ~ 2-14 Mbps
	        case TelephonyManager.NETWORK_TYPE_HSUPA:	//9
	            return true; // ~ 1-23 Mbps
	        case TelephonyManager.NETWORK_TYPE_HSPA:	//10
	            return true; // ~ 700-1700 kbps
	        case TelephonyManager.NETWORK_TYPE_IDEN:	//11
	            return false; // ~25 kbps
	        
//		        case TelephonyManager.NETWORK_TYPE_EHRPD:
//		            return true; // ~ 1-2 Mbps
//		        case TelephonyManager.NETWORK_TYPE_EVDO_B:
//		            return true; // ~ 5 Mbps
//		        case TelephonyManager.NETWORK_TYPE_HSPAP:
//		            return true; // ~ 10-20 Mbps
		        
//		        case TelephonyManager.NETWORK_TYPE_LTE:
//		            return true; // ~ 10+ Mbps
	        
	        default:
	            return false;
		}
	}

}
