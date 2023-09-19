using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterManager : MonoBehaviour
{
    [SerializeField] PlayerManager playerManagerScript;

    [SerializeField] WaterShot water1;
    [SerializeField] WaterShot water2;
    [SerializeField] WaterShot water3;
    [SerializeField] WaterShot water4;

    // Update is called once per frame
    void Update()
    {
        water1.waterActive = false;                     
        water2.waterActive = false;
        water3.waterActive = false;
        water4.waterActive = false;

        if (playerManagerScript.Gun12Active)
        {
            water1.waterActive = true;
            water2.waterActive = true;
        }
        if(playerManagerScript.Gun23Active)
        {
            water2.waterActive = true;
            water3.waterActive = true;
        }
        if(playerManagerScript.Gun34Active)
        {
            water3.waterActive = true;
            water4.waterActive = true;
        }
        if(playerManagerScript.Gun41Active)
        {
            water4.waterActive = true;
            water1.waterActive = true;
        }
    }
}
