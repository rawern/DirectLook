#include "KinectMotor.h"

namespace DirectLook 
{
	KinectMotor::KinectMotor(void) : m_IsOpen( false )
	{
	} 
	
	KinectMotor::~KinectMotor(void) 
	{
		close();
	}

	bool KinectMotor::open(void) 
	{
		const XnUSBConnectionString* paths; 
		XnUInt32 count; 
		XnStatus res; 

		// Init OpenNI USB 
		res = xnUSBInit(); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBInit failed" ); 
			return false; 
		} 

		// Open "Kinect motor" USB device 
		res = xnUSBEnumerateDevices( 0x045E /* VendorID */, 0x02B0 /*ProductID*/, &paths, &count ); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBEnumerateDevices failed" ); 
			return false; 
		} 

		// Open first found device 
		res = xnUSBOpenDeviceByPath( paths[0], &m_Device ); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBOpenDeviceByPath failed" ); 
			return false; 
		} 

		XnUChar buf[1]; // output buffer 

		// Init motor 
		res = xnUSBSendControl( m_Device, (XnUSBControlType) 0xc0, 0x10, 0x00, 0x00, buf, sizeof( buf ), 0 ); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBSendControl failed" ); 
			close(); 
			return false; 
		} 

		res = xnUSBSendControl( m_Device, XnUSBControlType::XN_USB_CONTROL_TYPE_VENDOR, 0x06, 0x01, 0x00, NULL, 0, 0 ); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBSendControl failed" ); 
			close(); 
			return false; 
		} 
		
		// Connection to kinect motor was successful
		return true;
	} 

	void KinectMotor::close(void) 
	{ 
		if(m_IsOpen)
		{ 
			xnUSBCloseDevice( m_Device ); 
			m_IsOpen = false; 
		}
	} 

	bool KinectMotor::move( int angle ) 
	{
		XnStatus res; 

		// Send move control request 
		res = xnUSBSendControl( m_Device, XN_USB_CONTROL_TYPE_VENDOR, 0x31, angle, 0x00, NULL, 0, 0 ); 
		if(res != XN_STATUS_OK)
		{ 
			xnPrintError( res, "xnUSBSendControl failed" ); 
			return false; 
		}

		// It was succseeful to control the kinect motor
		return true;
	}
};
