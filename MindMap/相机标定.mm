<map version="1.1.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1688636297532" ID="ID_1101609885" MODIFIED="1688640833778" TEXT="&#x76f8;&#x673a;&#x6807;&#x5b9a;">
<node CREATED="1688636361674" ID="ID_1768444501" MODIFIED="1688636680971" POSITION="right" TEXT="&#x521d;&#x59cb;&#x5316;&#x76f8;&#x673a;">
<icon BUILTIN="full-1"/>
<node CREATED="1688636378582" ID="ID_246953184" MODIFIED="1688636413664" TEXT="Devices::MV_Camera mv_camera{&#x76f8;&#x673a;&#x5730;&#x5740;}"/>
</node>
<node CREATED="1688636418382" ID="ID_1880809892" MODIFIED="1688638578882" POSITION="left" TEXT="&#x6253;&#x5f00;&#x76f8;&#x673a;">
<icon BUILTIN="full-3"/>
<node CREATED="1688636534228" ID="ID_900626437" MODIFIED="1688638663731" TEXT="&#x8c03;&#x7528;&#xff1a;MV_Camera::open()">
<icon BUILTIN="full-1"/>
<node CREATED="1688636564759" ID="ID_1937876957" MODIFIED="1688636722721" TEXT="&#x68c0;&#x67e5;&#x76f8;&#x673a;&#x662f;&#x5426;&#x6253;&#x5f00;">
<icon BUILTIN="full-1"/>
<node CREATED="1688636599550" ID="ID_569409049" MODIFIED="1688636627775" TEXT="if(isopen())"/>
</node>
<node CREATED="1688636708413" ID="ID_973492765" MODIFIED="1688636879352" TEXT="&#x83b7;&#x5f97;&#x8bbe;&#x5907;&#x4fe1;&#x606f;&#xff0c;&#x5373;&#x662f;&#x5426;&#x53d1;&#x73b0;&#x8bbe;&#x5907;">
<icon BUILTIN="full-2"/>
<node CREATED="1688636879854" ID="ID_765566583" MODIFIED="1688637064135" TEXT="&#x83b7;&#x53d6;&#x8bbe;&#x5907;&#x4e2a;&#x6570;&#x4fe1;&#x606f;">
<icon BUILTIN="full-1"/>
<node CREATED="1688637065843" ID="ID_268056372" MODIFIED="1688637073190" TEXT="MV_CHECK_API_ERROR(CameraEnumerateDevice(infos, &amp;dev_num), &quot;&quot;);"/>
</node>
<node CREATED="1688636935840" ID="ID_596969912" MODIFIED="1688637046821" TEXT="&#x5982;&#x679c;&#x8bbe;&#x5907;&#x4e2a;&#x6570;&#x4e0d;&#x6ee1;&#x8db3;dev_num &gt; 0&#xff0c;&#x5219;&#x62a5;&#x9519;&quot;&#x672a;&#x53d1;&#x73b0;&#x8bbe;&#x5907;&quot;">
<icon BUILTIN="full-2"/>
<node CREATED="1688637053787" ID="ID_447943228" MODIFIED="1688637087772" TEXT="MV_ASSERT_ERROR(dev_num &gt; 0, &quot;&#x672a;&#x53d1;&#x73b0;&#x8bbe;&#x5907;&#xff01;&quot;);"/>
</node>
<node CREATED="1688638078039" ID="ID_813695477" MODIFIED="1688638321463" TEXT="&#x83b7;&#x53d6;&#x76f8;&#x673a;&#x53e5;&#x67c4;&#x4e2a;&#x6570;">
<icon BUILTIN="full-3"/>
<node CREATED="1688638323156" ID="ID_1752939023" MODIFIED="1688638341973" TEXT="MV_CHECK_API_ERROR(CameraInit(&amp;infos[0], PARAM_MODE_BY_MODEL, -1, &amp;handle), &quot;&quot;);"/>
</node>
<node CREATED="1688638479922" ID="ID_1174921955" MODIFIED="1688638528184" TEXT="&#x5982;&#x679c;&#x53e5;&#x67c4;&#x4e2a;&#x6570;&#x4e0d;&#x6ee1;&#x8db3; handle &gt;= 0&#xff0c;&#x5219;&#x62a5;&#x9519;&#x201c;&#x76f8;&#x673a;&#x672a;&#x627e;&#x5230;&#x201d;">
<icon BUILTIN="full-4"/>
<node CREATED="1688638530699" ID="ID_652857518" MODIFIED="1688638550638" TEXT="MV_ASSERT_ERROR(handle &gt;= 0, &quot;&#x76f8;&#x673a;&#x672a;&#x627e;&#x5230;&#xff01;&quot;);"/>
</node>
</node>
</node>
<node CREATED="1688638677891" ID="ID_93928346" MODIFIED="1688640662580" TEXT="&#x8fdb;&#x5165;&#x5faa;&#x73af;">
<icon BUILTIN="full-2"/>
<node CREATED="1688640663809" ID="ID_1725149187" MODIFIED="1688640683534" TEXT="timer.start(0);">
<icon BUILTIN="full-1"/>
<node COLOR="#ff0000" CREATED="1688640685268" ID="ID_1998720413" MODIFIED="1688640882753" TEXT="&#xff1f;&#xff1f;&#xff1f;&#xff1f;"/>
</node>
<node CREATED="1688640690852" ID="ID_404620026" MODIFIED="1688640700396" TEXT="&#x8bfb;&#x53d6;&#x56fe;&#x7247;">
<icon BUILTIN="full-2"/>
<node CREATED="1688640703977" ID="ID_109609713" MODIFIED="1688640793859" TEXT="MV_Camera::read(cv::Mat &amp; img) const"/>
</node>
</node>
</node>
<node CREATED="1688638459305" ID="ID_1780548559" MODIFIED="1688638469780" POSITION="right" TEXT="&#x8ba1;&#x65f6;">
<icon BUILTIN="full-2"/>
</node>
<node CREATED="1688686201338" ID="ID_1900155588" MODIFIED="1688686204426" POSITION="left" TEXT="">
<icon BUILTIN="full-4"/>
</node>
</node>
</map>
