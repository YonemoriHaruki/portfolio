using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPos : MonoBehaviour
{
    public int playerPos;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(transform.position.x <= 0 && transform.position.z <= 0)          //X- : Y-
        {
            playerPos = 0;
        }
        if (transform.position.x <= 0 && transform.position.z >= 0)          //X- : Y+
        {
            playerPos = 1;
        }
        if (transform.position.x >= 0 && transform.position.z >= 0)          //X+ : Y+
        {
            playerPos = 2;
        }
        if (transform.position.x >= 0 && transform.position.z <= 0)          //X+ : Y-
        {
            playerPos = 3;
        }
    }
}
