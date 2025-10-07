# Common Installations

## Moving Picking Area and Fixed Placing Area

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759546848483_769c9c9d-96e6-4b78-81f7-42a4b044480f.png?alt=media&token=4d465e31-5819-4fcb-92ef-e0cde9eb3bbc)

### Camera Calibration

#### Adjust Perspective
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759652851042_0886551a-07c8-452d-accd-aef9420db851.jpg?alt=media&token=cfba8267-fc77-4a3d-85d7-d68b3123305d)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759653205111_0e66ca78-b3d2-4700-83f7-f55e82334f76.jpg?alt=media&token=7f523fda-3e69-4df1-a375-4b19ed2ae155)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759653297497_7642d059-596e-4e3c-9ef5-5be97a1065e6.jpg?alt=media&token=9e7240e0-1cf9-436c-b417-d2f6c68160f2)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759653386832_fdd36b18-edd7-4cd7-a994-5ee81bbf7d79.jpg?alt=media&token=b46f2333-4b67-4ef5-9d38-e52846101387)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759653459976_e057aa08-3cbb-4911-871e-8297dc34ed80.jpg?alt=media&token=bb589d04-de55-44f0-8e5b-726c190acbe8)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759655592768_04fd4708-33e8-4e85-bcfa-56280c1bcd13.jpg?alt=media&token=0d39bfe2-0736-4097-a11c-da211054d2eb)

##### Crop the Working Area

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759655619387_aec4e64a-8106-4a92-b75c-140a1a42a09e.jpg?alt=media&token=2478ef02-3cbb-4d82-a3c6-ae7403113942)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759655650135_87b8ac15-7a01-40c0-9682-9a95ea160aba.jpg?alt=media&token=9f3ab2c1-aefc-418c-ad7d-4d82fdf53fe7)

### Set up mapping between coordinate systems

#### From image to conveyor
1. **Select the “Select Calibration Point” tool.**
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759663704069_116113d4-e639-4f08-a52f-a07756af7393.jpg?alt=media&token=4a3d15bb-0d11-4c3b-b54a-2cd7242e3dee)
2. **Click on a marked point on the chessboard, referred to as T.**
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675251924_b1696f3c-c360-46ec-9101-8e1918cacd72.jpg?alt=media&token=742fafe1-f4d5-4831-a7d1-8542ea3c2aa7)
   Here, I select the center of the blue circle at the bottom-right corner.
   Enter the coordinates of point T on the conveyor here (**Calibration → P1'**).
   Set **X = 0**. If an encoder is used, set **Y** to the encoder’s value; otherwise, set **Y = 0**.
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675279243_4d79adde-06fe-4269-8fed-d1d2c7a25cde.jpg?alt=media&token=ea719c8a-7021-4469-bc03-3c5a59dcfeba)
3. **Move the conveyor by 80 mm.**
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675344993_c80702f2-43c9-47c1-93a0-aef61b59cf77.jpg?alt=media&token=7d8c5a6c-dfa0-4a78-bc8b-239342b17059)
   Click on point **T** again in the image. This time, the coordinates of **T** are **P2'**.
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675684726_ab4b5e80-19d3-4853-b151-0a932b78b598.jpg?alt=media&token=afc250aa-b232-4ec6-8a43-6b8519aceee8)
   Again, set **X** of **P2' = 0**, and **Y** to the encoder’s value or **80 mm**.
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675774588_648f7c75-9096-4306-a414-19b2cec5f0e2.jpg?alt=media&token=94d7c103-10f0-41cf-87a7-96063c920910)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759675872107_cee4e8ae-eb3e-42b9-ba19-ffd185181ab5.jpg?alt=media&token=9d1d5000-1731-4d00-980e-17d191b1de4f)
#### From conveyor to robot
![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759676812728_b9e41248-eb40-42ae-b45e-a1b5251dfb6d.jpg?alt=media&token=0ed585ed-d8e6-43d1-bc2a-fb8827262b47)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677002006_cb11b6ea-abd3-4706-bc44-ed98b6b138ea.jpg?alt=media&token=a7e0d66e-1460-4a32-aec5-490371553d86)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677019898_3aea110f-eace-4d2b-940c-c6671ddcff4f.jpg?alt=media&token=1296a138-1b27-4f64-acdc-389761d6b02f)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677580926_f5f607fe-dfdb-455c-bb87-336607512684.jpg?alt=media&token=bdcdff64-900a-4c4b-81cc-af8d04453616)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677612486_ee338757-9802-4bb9-8f22-061afac4c816.jpg?alt=media&token=884cbe5a-cb75-49ba-b093-7b96a236f508)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677633320_e6eac681-1b80-4134-9011-d26f69cc11de.jpg?alt=media&token=d4c61e52-4dd6-422a-b6f7-d62dc1c49be8)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677646646_18874f67-69eb-472c-8622-7754506daec4.jpg?alt=media&token=fcb368b4-6edf-47cb-aedd-0d0f61dca33e)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677663929_52b05b33-7525-475c-bc94-9bf0faf3bc1c.jpg?alt=media&token=5b01b8d2-9186-4ee7-b4c2-03e2c4a1f67b)

![Image](https://firebasestorage.googleapis.com/v0/b/deltax-hub.firebasestorage.app/o/documents%2Fdefault-company%2Fimages%2F1759677682392_604a35b1-58fb-47c2-893a-f9755fee733d.jpg?alt=media&token=c15e155e-ee2e-451d-8943-a25dc9afa3bc)

#### Find the conveyor’s movement vector in the robot’s coordinate system