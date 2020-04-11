# LRVent: 3D Printed BVM Ventilator

[![LRVent Mk2 Overview Video](https://img.youtube.com/vi/VjBAnV-SXSI/0.jpg)](https://www.youtube.com/watch?v=VjBAnV-SXSI)



Patients with COVID-19 in serious or critical condition often require assisted breathing via ventilator. As the number of patients in need of ventilators grows (exponentially in many densely populated regions), there are not adequate numbers of ventilators to support the high number of patients.

**This project aims to provide a very basic, last resort ventilator design that can be built quickly with locally sourced parts (from hardware and automotive stores) and maker-level tools (hand tools and a 3D printer).** 

<img src="./Images/2020-04-11 - LRVentMk2 CAD view.png" style='max-height:240px;'/>

The basic structure of the device is intended to span a large range of parts depending on what can be found locally (various fasteners, bearings, motors, and electronics) and can be easily extended to accommodate new components as needed. It is also designed to span a wide range of technical capabilities (from simply plugging in power to a motor, up to Arduino-level software and electronics to add basic controls for breathing rate and inspiratory/expiratory ratio).

As with any medical device hack, this has been created with the intention of being as safe as possible given the harsh constraints of the current global pandemic and ventilator shortage, but is **UNCERTIFIED, HIGHLY EXPERIMENTAL, and UNTESTED ON HUMANS.** As such, any potential use scenario would also require **legal waivers to use uncertified/untested non-medical devices** and **significant additional patient monitoring by medical professionals and certified diagnostic equipment** to reduce the risk of serious consequences in the event that the device fails to operate as intended by doctors. The **core contributors to this project are not medical professionals**.

Also note that lungs are very delicate organs, and **inappropriate use/testing of any ventilator can cause severe trauma to the lungs.** This is intended for medical professionals as a last resort under their professional judgement and supervision in desperate times. **Don't test the device on yourself or your friends. Don't even test it on your dog. You have been warned.** 

LRVent is released as public domain (Creative Commons Zero v1.0 Universal) for anyone to use, modify, share, produce, etc. with no strings attached.

## Disclaimer

This project is aligned with [OpenLung](https://gitlab.com/open-source-ventilator/OpenLung/-/tree/master)'s project goals, and as such carries with it the same umbrella disclaimer.

*The plans, documents and other materials (“Material”) contained on this website are intended to facilitate the design of a prototype reproducible medical device to be used if required during the Covid-19 pandemic. The Material is not itself a medical device. The Material has not been tested and has not been approved for use in humans or animals by any regulatory authority of any country.*

*By using the Material, you are agreeing to the following disclaimer.*

*The project offers the Material as-is and as-available, and makes no representations or warranties of any kind whatever concerning the Material, whether express, implied, statutory, or other. This includes, without limitation, warranties of merchantability, fitness for a particular purpose, non-infringement, absence of latent or other defects, accuracy, or the presence or absence of errors, whether or not known or discoverable.*

*To the extent possible, in no event will the contributors of this project be liable to you on any legal theory (including, without limitation, negligence) or otherwise for any direct, special, indirect, incidental, consequential, punitive, exemplary, or other losses, costs, expenses, or damages arising out of the Material or use of the Material, even if the contributors has been advised of the possibility of such losses, costs, expenses, or damages.*

***Any ventilator system that has not been approved by a competent medical device regulatory authority may not deliver to the user the ability to properly monitor and control tidal volume, inspiratory pressure, inspiratory/expiratory ratio, heart rate, nor provide the user with the ability to monitor and control positive-end expiratory pressure (PEEP), peak inspiratory pressure (PIP) or to adapt to individual patient requirements.  Inability to monitor and/or control any of these factors can cause death or serious permanent injury.***

*The disclaimer of warranties and limitation of liability provided above shall be interpreted in a manner that, to the extent possible, most closely approximates an absolute disclaimer and waiver of all liability.*



## When to consider building/using LRVent

As its name implies, LRVent should be used as a last resort. Generally, medical professionals are likely to consider ventilation in this order:

1. Approved/certified ventilators used as designed on a single patient.
2. Secondary ways to extend resources (such as splitting a single ventilator's output to multiple patients, or refurbishing decommissioned units) or leveraging/modifying other certified devices (such as a BiPAP/CPAP machines).
3. Anything else that medical professionals deem appropriate for the given patient/circumstance.
4. Other more capable quick-build ventilator efforts (OpenLung, quick-turn manufacturing initiatives, etc...).
5. Seriously... anything else that may be medically beneficial.
6. Okay, as a ***very last resort***, this project (LRVent).



## LRVent Approach

Tenets for the LRVent design:

* Leverage **medical equipment that's not in short supply.** 
  * A <u>Bag-Valve-Mask</u> (BVM, used for manual ventilating) is sterile and has standard fittings for various valves and supply lines. BVM are also standard in most hospital/ambulance settings, likely already on-hand, and typically cost less than $50 each.
  * Existing <u>certified and highly-capably monitoring equipment</u> (heart rate, blood oxygen, etc.) are often tightly integrated with broader hospital monitoring/notification systems for critical care. While adding fail-safe monitoring and alerts/lights/buzzers to the LRVent may seem like an important feature, there's a risk of then relying on them to notify staff and this project should in no way be perceived as reliable for life-critical use.
* Leverage **reliable, mass-produced parts where possible.**
  * To repeatedly press on a BVM, a fairly powerful mechanical-electrical actuator is needed that can run constantly for 30+ days. Many automative parts fit nicely into this category, especially <u>windshield wiper motors</u> that have built-in functionality to "park" the wipers after a complete revolution. This can ideally be leveraged to complete a full revolution (a BVM push/return cycle) and then rest until the next breath is desired without needing additional sensors.
  * <u>Standard metric fasteners and bearings</u> that can be found at local hardware stores. US hardware stores often carry metric fasteners as well, but may be located in another area.
* Leverage **broadly accessible, maker-level tools.**
  * <u>Hand tools and a 3D printer</u> should be about all the tools that are needed. Don't assume laser cutters, water jet cutters, CNC machines, lathes, mills, etc. as this greatly limits who can build one. If you have access to a full machine shop and/or trained fabrication staff, consider a more production-centric ventilator project.
  * In terms of printing, while some materials are much tougher than PLA (such as ABS and PETG), LRVent should be designed to be <u>fully functional when printed in PLA</u> since that is what most maker spaces and/or home workshops already have in large supply. 
* Span a **wide range of locally sourced components.**
  * <u>Splitting the design into modular pieces</u> that can fit a wide range of parts enables more people to make devices. For example, various windshield wiper motors have different bolt patterns to attach them to cars, and thus where the motor mounts to LRVent should be a part that can be selected/modified to fit.
* Span a **wide range of skillsets.**
  * A <u>novice maker</u> should be able to buy/print the relevant parts, plug in power, and have the device start pumping. It may be less than optimal, but from there, further hacks (like mechanically spacing the BVM away from the stand to change the tidal/breath volume) could be employed.
  * For <u>more advanced makers</u>, using an additional Arduino-capable microcontroller, a couple FET transistors, a couple potentiometers, and a soldering iron should be enough to quickly build/program a basic controller to allow for adjusting the breathing rate and the inspiratory/expiratory ratio.
* Always **allow for manual intervention.**
  * The BVM should <u>remain accessible to hand pumping</u> when needed. If the motor stops and medical staff are notified (by other connected devices), a person should be able to immediately begin pumping by hand to continue the supply of air while the issue is resolved. Note that this may be partially at odds with avoiding a "pinch point" where a user could inadvertently place their hand in the device's motor/actuation path and injure themselves (which must be avoided as much as possible), but access to the patient's air supply is given highest priority.
* **Completely open/free for the world.**
  * Released under <u>Creative Commons 0 / Public Domain</u>. No strings attached. If you have ideas for improvement, just do it (then of course feel free to let us know and/or fork the repo and share your changes if you think others may find it useful, too). For your own safety, and the safety of others, please continue to include the disclaimer and be mindful to convey the **UNCERTIFIED, HIGHLY EXPERIMENTAL, and UNTESTED** nature of this project.



## LRVent Operation

Like many bag-squeezer ventilator projects that have come before, the idea is quite simple; repeatedly squeeze a semi-rigid bag (BVM / Ambu bag) to deliver air to the patient. 

* **Respiratory rate** (*RR*) is controlled by how often/quickly the bag is squeezed. This is typically set in the range of 8-16 breaths/min, but with COVID-19 patients, using a slightly faster breathing rate (*RR* between 12-20 breaths/min) with less volume seems preferable/likely.
* **Tidal volume** (*Vt*, the amount of air per breath) is controlled how far the bag is squeezed. This is typically set in the range of 350-450mL, but with COVID-19 patients, using a slightly faster breathing rate at lower a *Vt* seems preferable/likely (closer to 200-300mL).
* **Inspiratory/Expiratory ratio** (*Ip/Ep*) is controlled by speed changes between the squeeze and the release portion of each breath.
* **Fraction of inspired oxygen** (*FiO2*) controlled by air/oxygen mix supplied to the BVM's port.



In its **<u>simplest form</u>**: 

* a motor can be driven directly from a power supply (ideally at a voltage that produces squeezing at a typical **Respiratory Rate**; a variable voltage supply is greatly helpful here).
* The **Inspiratory/Expiratory Ratio** is determined by a constant turning speed of the motor (approx. 50%).
* The **Tidal Volume** is set by the placement of the bag relative to the pusher arm. Placing the bag closer engages the pusher for the whole stroke and delivers a larger volume of air. Placing the bag farther from the pusher reduces the volume that is delivered to the patient.



As an **<u>extension</u>** to the simplest form, a **<u>controller can be added</u>**, along with some basic electronics, to more precisely adjust the breathing rate and inspiratory/expiratory ratio from a fixed voltage power supply:

* The voltage driving the motor can be modulated to vary the rate of motion throughout a breath cycle, allowing for the **coarse adjustment of Inspiratory/Expiratory Ratio**.
* By using the windshield wiper motor's "park" functionality, the controller can also more **precisely set the Respiratory Rate**, allowing for a rest/null portion of the breath.
* The **Tidal Volume** is still set mechanically by changing the position/proximity of the bag to the pusher arm.

## Parts List

In addition to the 3D printed parts (in the `PrintFiles` directory), you'll need a few other things:

* **Windshield Wiper Motor**. You can use pretty much any wiper motor, but you'll need to modify the design to properly hold the motor in place and attach to the *WiperArm*. 

  So far, wiper motors for these vehicles have been implemented/tested:

  * **Dodge Ram (1997-1999)**: *Cardone 85-3000*, *Cardone 40-3000*, or similar.
  * more to come as parts are tested...

* **4 x 608 Ball Bearings**: #608ZZ, #6082RS, or similar.

* **4 x M3x(5-8mm long) socket head bolts**: These hold the bearings in place. 

* **24 x M3x(12-15mm long) socket head bolts**: These are used to fasten all of the 3D printed parts together.

* **6 x M3 Locknuts:** These secure the adjustment posts that hold the BVM at a specific height.

* **6 x M3 Washers**: These are used under the head of the bolts with locknuts to spread out the force when tightened.

* **1 x M8x(40-45mm long) hex head bolt**: This provides the primary fulcrum/shaft for the pusher arm.

* **1 x M8 Locknut**: This holds the M8 bolt in place.

* **2 x M5x(20-30mm long) socket head bolts**: These are used in the center/shafts of the pusher arm linkages to secures the bearings to the driven parts.

* **2 x M5 Locknuts**: These hold the M5 bolts in place.

* **1" wide sew-on velcro nylon strap**: This wraps over the top and secures the BVM in place.

* **1 x Heavy Duty Rubber Band**: This holds the neck of the BVM in place so it doesn't drift as the devices runs.



## Mechanical Assembly

Note: This design leverages the ability for printed parts to have self-tapping holes (using a bolt directly without pre-cut threads). This seems to work quite well, but **take care not to over-tighten bolts into 3D printed parts** to reduce the risk of stripping the plastic.

1. To assemble the LRVent, start by bolting together the *FrameSideWM_xyz* (specific to the wiper motor you are using) to the *FrameBack* and the *FrameBase* with 5 x M3x(12-15mm long) bolts.
2. Next, bolt on the Wiper Motor to the *FrameSideWM_xyz* with the motor's supplied fasteners.
3. Press a 608 bearing into the *WiperArm*, and secure in place with 2 x M3x(5-8mm) bolts.
4. Press 3 x 608 bearings into the pusher arm. Secure the single bearing near the pushing end with 2 x M3x(5-8mm) bolts.
5. ... (in progress)



## Electrical Assembly

In progress.

## Programming 

In progress.

## Testing

In progress.

## Modifications

In progress.