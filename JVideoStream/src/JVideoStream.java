/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

/**
 *
 * @author MobMonRob
 */
public class JVideoStream {

    static {
	//System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	//System.loadLibrary("PylonOpenCvSwingWrapper");
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
	// TODO code application logic here
	//System.out.println("hello");

	//Mat mat = Mat.eye(3, 3, CvType.CV_8UC1);
	//System.out.println("mat = " + mat.dump());

	System.out.println(System.getProperty("java.library.path"));
	Thread.sleep(100);

	System.loadLibrary("PylonOpenCvSwingWrapper");
	Shape asdf = new Shape(5);
    }
}
