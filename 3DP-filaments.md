# 3D Printing Mega Chart (Sorted by Filament Type)

| **Filament**            | **Nozzle Temp (°C)** | **Bed Temp (°C)** | **Chamber Temp (°C)** | **Airflow** | **Hardened Nozzle** | **Flexible / Brittle** | **Water Resistance** | **Best Bed Sheet**         | **Recommended Brands**                              |
|-------------------------|----------------------|-------------------|------------------------|-------------|----------------------|-------------------------|------------------------|-----------------------------|-----------------------------------------------------|
| **PLA+**                | 200-220              | 50-60             | None / Ambient         | On          | Not needed           | Slightly brittle        | Low                    | PEI, Smooth or Textured     | Polymaker PLA Pro, eSUN PLA+, Prusament PLA         |
| **ABS**                 | 230-250              | 90-110            | 60+                    | Off         | Not needed           | Brittle                 | Moderate               | PEI Textured, ABS Slurry     | Hatchbox, Prusament ABS, eSUN ABS+                  |
| **ASA**                 | 240-260              | 90-110            | 60+                    | Off         | Not needed           | Brittle                 | High (UV-resistant)    | PEI Textured                | Polymaker ASA, Fillamentum ASA, Prusament ASA       |
| **PETG**                | 230-250              | 70-90             | ~45 (optional)         | Minimal     | Not needed           | Slightly flexible       | High                   | PEI Smooth (glue stick)     | Prusament PETG, Polymaker PETG, Overture PETG       |
| **TPU (95A)**           | 220-240              | 40-60             | Ambient                | On          | Not needed           | Flexible                | High                   | PEI Smooth                  | NinjaTek Cheetah, Polymaker PolyFlex, Sainsmart     |
| **PC (Polycarbonate)**  | 260-310              | 100-120           | 80+                    | Off         | Recommended          | Brittle                 | High                   | Garolite, PEI               | Polymaker PC-Max, Prusament PC Blend, MatterHackers |
| **PA (Nylon)**          | 240-270              | 70-90             | 60-70                  | Off         | Yes (wear-resistant) | Flexible                | High (but absorbs)     | Garolite, Glue stick        | Taulman 910, Polymaker PA6-CF, eSUN ePA              |
| **NylonX (CF Nylon)**   | 250-270              | 75-90             | 60-70                  | Off         | **Required**         | Rigid / Tough           | High                   | Garolite, PEI with glue     | MatterHackers NylonX, 3DXTech CF Nylon              |
| **Glass-Filled Nylon**  | 260-280              | 80-100            | 70-80                  | Off         | **Required**         | Rigid / Tough           | High                   | Garolite, PEI with glue     | Polymaker PA6-GF, 3DXTech Glass Fiber Nylon          |
| **Carbon Fiber PETG**   | 240-260              | 75-85             | 50+                    | Minimal     | Required             | Rigid                   | High                   | PEI Textured                | Priline CF PETG, 3DXTech CF PETG, Polymaker PAHT-CF |
| **Ultem (PEI)**         | 350-390              | 140-160           | 90-110                 | Off         | Required             | Very rigid              | Extremely high         | PEI or Garolite (bonded)    | 3DXTech Ultem 1010, Sabic Ultem 9085                 |
| **PPSU**                | 360-400              | 120-160           | 90+                    | Off         | Required             | Tough / Slightly flexible | High                | Garolite or PEI             | 3DXTech PPSU, SABIC PPSU                             |
| **PBT**                 | 240-270              | 100-120           | 70+                    | Off         | Recommended          | Brittle                 | High                   | PEI or Garolite             | Nexeo PBT, Polymaker PolyLite PBT                    |
| **HIPS**                | 230-240              | 90-110            | 50-60                  | Off         | Not needed           | Brittle                 | Moderate               | PEI Textured                | eSUN HIPS, ZYLtech HIPS, Polymaker HIPS              |

---

### Legend / Tips:
- **Airflow Off** = Turn off part cooling fan for layer adhesion.
- **Garolite** = G10/FR4 sheet; ideal for Nylons and PC.
- **Glue Stick** = Use to reduce over-adhesion or increase grip.
- **Dry Box** = Essential for Nylon, PC, CF/GF variants to prevent bubbling and poor strength.

---

# Filament Use-Case Reference Guide

| **Filament**         | **Best / Common Use-Cases**                                                                 | **Where It Should *Not* Be Used**                                                                 |
|----------------------|---------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|
| **PLA+**             | Prototypes, figurines, cosplay, basic mechanical parts, low-stress enclosures               | Outdoors, high-heat environments, flex or impact-loaded parts                                       |
| **ABS**              | Automotive interior parts, enclosures, functional parts, solvent-welded assemblies          | Cold or poorly ventilated spaces, thin wall or fine detail models (warping, cracking risk)         |
| **ASA**              | Outdoor enclosures, weatherproof parts, UV-exposed signage                                 | Unheated chambers or printers with poor temperature stability                                       |
| **PETG**             | Food-safe containers (check MSDS), mechanical brackets, moisture-resistant prints           | Tight tolerances (stringy), overly flexible components, high-heat parts (>80°C)                    |
| **TPU (95A)**        | Phone cases, gaskets, vibration dampening feet, cable organizers                           | Rigid structures, high-load parts, tight-tolerance gear mechanisms                                  |
| **PC (Polycarbonate)**| High-impact parts, load-bearing brackets, transparent parts, protective housings           | Printers with weak chamber heating or no enclosure (it warps aggressively)                         |
| **Nylon (PA)**       | Gears, hinges, clips, impact-resistant mechanical parts, jigs & fixtures                    | Wet environments without post-drying, tight tolerance or thin-walled parts due to warping           |
| **NylonX (CF Nylon)**| Functional end-use parts, drone frames, high-stress mechanical components                   | Decorative prints, flexible components, non-abrasive nozzles                                        |
| **Glass-Filled Nylon**| High rigidity brackets, structural parts, heat-resistant applications                      | Parts requiring flexibility or vibration resistance, unsupported printers (warping/cracking)        |
| **CF PETG**          | RC car parts, stiff brackets, flat panels, tough enclosures                                | Decorative or clear prints (CF dulls appearance), parts requiring flexibility                       |
| **Ultem (PEI)**      | Aerospace, automotive, high-temp connectors, sterilizable medical parts                     | Non-industrial printers, hobby-level applications, transparent aesthetic models                     |
| **PPSU**             | Sterilizable surgical guides, chemical-exposed parts, flame-retardant components           | Printers not rated for 400°C+ nozzle temps, aesthetic prints, cost-sensitive projects               |
| **PBT**              | Electrical connectors, automotive switches, chemically-resistant parts                      | Decorative models, unsupported parts needing good bed adhesion (can warp)                           |
| **HIPS**             | Support material for ABS, lightweight enclosures, prototyping                              | Structural parts, anything exposed to high moisture (absorbs and weakens), decorative models       |

---

### Notes:
- **CF/GF Composites** = Amazing for rigidity, but will rapidly wear out brass nozzles.
- **Drying Required** = Especially important for Nylon, PC, and PBT.
- **Ultem & PPSU** = Truly industrial-use only; overkill for 99% of hobby printing needs.