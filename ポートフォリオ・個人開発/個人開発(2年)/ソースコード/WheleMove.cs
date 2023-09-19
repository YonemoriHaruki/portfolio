using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WheleMove : MonoBehaviour
{
    [SerializeField] 
    float speed = 1f;

    public bool XMove;
    public bool YMove;
    public bool ZMove;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (XMove)
        {
            transform.position += new Vector3(speed, 0, 0) * Time.deltaTime;
        }
        if (YMove)
        {
            transform.position += new Vector3(0, speed, 0) * Time.deltaTime;
        }
        if(ZMove)
        {
            transform.position += new Vector3(0, 0, speed) * Time.deltaTime;
        }
       
    }
}
