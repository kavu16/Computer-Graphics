using UnityEngine;
using System.Collections;

public class CatmullRomStEd : MonoBehaviour
{
	public Transform[] controlPoints;
	
	//Play in the editor mode, no need to work in the game mode
	void OnDrawGizmos()
	{
		Gizmos.color = Color.blue;

		for (int i = 0; i < controlPoints.Length; i++)
			DisplayCatmullRomSpline(i);
	}

	
	void DisplayCatmullRomSpline(int pos)
	{
		//Here, you need to draw a line (draw a spline) in between 2 points
		//Catmull-Rom algorithm for deriving points: 

		//Create 4 Vector3 points to form a spline between p1 and p2
		//Since our spline is looped, be sure that for end and start points, you 
		//do find proper indices in your range 0..n-1 for your connections, so call 
		//CorrectIndex function if necessary

		//E.g/
		Vector3 p0 = controlPoints[0].position;
		Vector3 p1 = controlPoints[1].position;
		Vector3 p2 = controlPoints[2].position;
		Vector3 p3 = controlPoints[3].position;

		//The start position of our line is p1 and it is defined here
		Vector3 px = p2;

		//How many times should we loop? 5 for our initial case. 
		//TODO..Try different number of control points and different loop numbers here
		int loop_num = 5;
		for (int i = 1; i <= loop_num; i++)
		{
			////TODO..parameter t can be computed as 1/loop number * i
			float t = (i/loop_num);
			Vector3 py = SolveCatmullRom(t, p0, p1, p2, p3);
			Gizmos.DrawLine(px, py);
			px = py;
		}
	}

	//Index control for looping
	int CorrectIndex(int index)
	{
		if (index < 0)
			index = 0;
		else if (index > controlPoints.Length)
			index = controlPoints.length - 1;
		else if (index >= controlPoints.Length)
			index = controlPoints.length - 2;

		return index;
	}

	
	Vector3 SolveCatmullRom(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
	{
		//Decide about the coefficients a, b, c and d
		//one example is:
		//a = 2p1
		//b=p2-p0
		//c=-p3+4p2-5p1+2p0
		//d=p3-3p2+3p2-p0

		Vector3 a = p1;
		Vector3 b = 0.2*(p2 - p0);
		Vector3 c = 3*(p2 - p1) - 0.2*(p3 - p1) - 2*(0.2)*(p2 - p0);
		Vector3 d = -2*(p2 - p1) + 0.2*(p3 - p1) + (0.2)*(p2 - p0);

		
		Vector3 pos = a + (b*(t)) + (c*(t^2)) + (d*(t^3)); //TO DO: //The cubic polynomial: a + b * t + c * t^2 + d * t^3
		return pos;
	}
}
