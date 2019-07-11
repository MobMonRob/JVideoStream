/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jvideostream;

import swingWrapper.PylonOpenCvSwingWrapperJNI;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

/**
 *
 * @author MobMonRob
 */
public class JVideoStream {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
	// TODO code application logic here
	System.out.println("hello");

	System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	Mat mat = Mat.eye(3, 3, CvType.CV_8UC1);
	System.out.println("mat = " + mat.dump());
	
	PylonOpenCvSwingWrapperJNI test = new PylonOpenCvSwingWrapperJNI();
	PylonOpenCvSwingWrapperJNI.new_Circle(0);
    }
}
