# Smart Waste Segregation System (S³) ♻️🤖

## Overview
This repository contains the embedded C++ logic for the **Smart Waste Segregation System (S³)**. Designed to support sustainable smart city infrastructure, this automated cyber-physical prototype uses multi-sensor fusion to classify and mechanically route waste into distinct categories (Metal, Wet/Organic, and Dry).

## Hardware Architecture
The system integrates simultaneous environmental inputs, processed by a central microcontroller to trigger real-time mechanical actuation without cross-talk or hardware blocking.
* **Microcontroller:** Arduino Uno
* **Presence Detection:** HC-SR04 Ultrasonic Sensor (Triggers the scanning sequence)
* **Material Classification (Metal):** LJ12A3-4-Z/BX Inductive Proximity Sensor
* **Material Classification (Organic/Wet):** Analog Moisture/Rain Sensor
* **Actuation:** MG996R Servo Motor (Mechanically routes the waste slider)

## Operational Workflow
1. **Detection:** The HC-SR04 continuously pings the entry hopper. When an object breaks the distance threshold, the main classification loop is triggered.
2. **Sensor Fusion & Classification:** 
   * The system polls the **inductive proximity sensor** to check for metallic signatures.
   * Simultaneously, it polls the **analog moisture sensor** to check for wet/organic conductivity.
3. **Actuation & Routing:** Based on a hierarchical C++ `if/else` control structure, the Arduino commands the MG996R servo motor to shift to a specific, hardcoded angle, dropping the waste into the corresponding bin.
4. **Reset:** The system holds the actuation angle to clear the hopper, then resets to the home position to await the next object.

## Research & Smart City Application
This prototype showcases core competencies in **hardware automation**, **sensor integration**, and **embedded systems logic**. It serves as a foundational step toward developing large-scale, autonomous environmental sustainability technologies.
