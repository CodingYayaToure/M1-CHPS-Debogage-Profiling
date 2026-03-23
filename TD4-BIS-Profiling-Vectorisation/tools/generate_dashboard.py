#!/usr/bin/env python3
import sys, os

data_file = sys.argv[1] if len(sys.argv) > 1 else "tests/runs/data/grall.data"
output    = sys.argv[2] if len(sys.argv) > 2 else "tests/runs/graphs/dashboard.html"

rows = []
with open(data_file) as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) >= 2:
            rows.append([int(x) for x in parts])

sizes   = [r[0] for r in rows]
columns = list(zip(*[r[1:] for r in rows]))

versions = [
    ("001-O2","float**","Référence r,c,d",         "ref"),
    ("001-O3","float**","Référence r,c,d",          "ref"),
    ("002-O2","float**","Loop Interchange r,d,c",   "good"),
    ("002-O3","float**","Loop Interchange r,d,c",   "good"),
    ("003-O2","float**","Tiling T=16 mauvais ordre","base"),
    ("003-O3","float**","Tiling T=16 mauvais ordre","base"),
    ("004-O2","float**","Tiling asymétrique",       "base"),
    ("004-O3","float**","Tiling asymétrique",       "base"),
    ("005-O2","float*", "1D macros r,d,c",          "good"),
    ("005-O3","float*", "1D macros r,d,c",          "good"),
    ("006-O2","float*", "Tiling T=64 + AVX",        "best"),
    ("006-O3","float*", "Tiling T=64 + AVX",        "best"),
    ("007-O2","float*", "Tiling + unroll",           "base"),
    ("007-O3","float*", "Tiling + unroll",           "base"),
    ("008-O2","float*", "Tiling + vars locales",     "base"),
    ("008-O3","float*", "Tiling + vars locales",     "base"),
    ("009-O2","float*", "Tiling + buffer B",         "base"),
    ("009-O3","float*", "Tiling + buffer B",         "base"),
    ("010-O2","float*", "AVX2 + FMA intrinsèques",  "best"),
    ("010-O3","float*", "AVX2 + FMA intrinsèques",  "best"),
    ("011-O2","float*", "AVX2 + FMA + OpenMP",      "best"),
    ("011-O3","float*", "AVX2 + FMA + OpenMP",      "best"),
]

ref_val = columns[0][-1] if columns else 1

data_js = "const SIZES = " + str(sizes) + ";\n"
data_js += "const VERSIONS = [\n"
for i, (name, sig, tech, cat) in enumerate(versions):
    if i < len(columns):
        vals = list(columns[i])
        gain = round(ref_val / vals[-1], 1) if vals[-1] > 0 else 0
        data_js += f'  {{name:"{name}", sig:"{sig}", tech:"{tech}", cat:"{cat}", data:{vals}, gain:{gain}}},\n'
data_js += "];\n"

html = f"""<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="UTF-8">
<title>ssgemm Performance Dashboard — Master 1 CHPS</title>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/4.4.1/chart.umd.js"></script>
<style>
* {{ box-sizing: border-box; margin: 0; padding: 0; }}
body {{ font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
       background: #f8f9fa; color: #1a1a1a; font-size: 14px; }}
.header {{ background: #1f3864; color: white; padding: 18px 28px; }}
.header h1 {{ font-size: 20px; font-weight: 500; }}
.header p  {{ font-size: 12px; opacity: 0.75; margin-top: 4px; }}
.nav {{ background: white; border-bottom: 1px solid #e0e0e0;
        padding: 0 28px; display: flex; gap: 0; }}
.nav button {{ padding: 12px 20px; border: none; background: none;
               font-size: 13px; color: #666; cursor: pointer;
               border-bottom: 2px solid transparent; }}
.nav button.active {{ color: #1f3864; border-bottom-color: #2e75b6;
                      font-weight: 500; }}
.content {{ padding: 24px 28px; }}
.section {{ display: none; }}
.section.active {{ display: block; }}
.metrics {{ display: grid; grid-template-columns: repeat(4,1fr);
            gap: 14px; margin-bottom: 24px; }}
.metric {{ background: white; border-radius: 8px; padding: 16px;
           border: 1px solid #e8e8e8; }}
.metric .val {{ font-size: 26px; font-weight: 600; color: #1f3864; }}
.metric .lbl {{ font-size: 11px; color: #888; margin-bottom: 6px; }}
.metric .sub {{ font-size: 11px; color: #aaa; margin-top: 4px; }}
.card {{ background: white; border-radius: 8px; border: 1px solid #e8e8e8;
         padding: 18px; margin-bottom: 18px; }}
.card h3 {{ font-size: 13px; font-weight: 500; color: #444;
            margin-bottom: 14px; }}
.chart-wrap {{ position: relative; width: 100%; height: 320px; }}
.two-col {{ display: grid; grid-template-columns: 1fr 1fr; gap: 16px; }}
table {{ width: 100%; border-collapse: collapse; font-size: 12px; }}
th {{ background: #f5f5f5; padding: 9px 12px; text-align: left;
      font-weight: 500; color: #555; border-bottom: 1px solid #e0e0e0; }}
td {{ padding: 8px 12px; border-bottom: 1px solid #f0f0f0; }}
tr:hover td {{ background: #fafafa; }}
.badge {{ display: inline-block; font-size: 10px; padding: 2px 8px;
          border-radius: 99px; font-weight: 500; }}
.badge-best {{ background: #e2efda; color: #375623; }}
.badge-good {{ background: #dce6f1; color: #1f3864; }}
.badge-base {{ background: #f2f2f2; color: #888; }}
.badge-ref  {{ background: #fce4d6; color: #843c0c; }}
.bar-row {{ display: flex; align-items: center; gap: 8px; margin-bottom: 7px; }}
.bar-lbl {{ font-size: 11px; color: #666; width: 90px; flex-shrink: 0; }}
.bar-track {{ flex: 1; height: 13px; background: #f0f0f0;
              border-radius: 3px; overflow: hidden; }}
.bar-fill {{ height: 100%; border-radius: 3px; }}
.bar-val {{ font-size: 11px; font-weight: 500; width: 42px; text-align: right; }}
.tma-grid {{ display: grid; grid-template-columns: repeat(3,1fr); gap: 14px; }}
.tma-card {{ background: white; border: 1px solid #e8e8e8;
             border-radius: 8px; padding: 14px; }}
.tma-card h4 {{ font-size: 12px; font-weight: 500; margin-bottom: 10px; }}
.controls {{ display: flex; gap: 10px; margin-bottom: 16px; align-items: center; }}
.controls select {{ font-size: 12px; padding: 6px 10px;
                    border: 1px solid #ddd; border-radius: 6px; }}
.best-row td {{ background: #f0fff4 !important; }}
</style>
</head>
<body>
<div class="header">
  <h1>ssgemm Performance Analysis Dashboard</h1>
  <p>Master 1 CHPS — Débogage, Profiling et Analyse de Performances &nbsp;|&nbsp;
     Université de Perpignan Via Domitia &nbsp;|&nbsp; 2025-2026 &nbsp;|&nbsp;
     Yaya Toure</p>
</div>

<div class="nav">
  <button class="active" onclick="show('overview',this)">Vue d'ensemble</button>
  <button onclick="show('progression',this)">Progression</button>
  <button onclick="show('perf',this)">Perf stat</button>
  <button onclick="show('tma',this)">Top-Down Yasin</button>
  <button onclick="show('versions',this)">Toutes les versions</button>
</div>

<div class="content">

<div class="section active" id="sec-overview">
  <div class="metrics" id="metricCards"></div>
  <div class="card">
    <h3>Cycles par version (N=1000) — O2</h3>
    <div class="chart-wrap"><canvas id="c-overview"></canvas></div>
  </div>
</div>

<div class="section" id="sec-progression">
  <div class="card">
    <h3>Progression des cycles selon la taille N — versions O2</h3>
    <div class="chart-wrap" style="height:380px;"><canvas id="c-prog"></canvas></div>
  </div>
  <div class="card">
    <h3>Zoom : versions optimisées (sans v001 référence)</h3>
    <div class="chart-wrap" style="height:320px;"><canvas id="c-zoom"></canvas></div>
  </div>
</div>

<div class="section" id="sec-perf">
  <div class="two-col">
    <div class="card"><h3>Cycles (N=1000)</h3>
      <div class="chart-wrap" style="height:240px;"><canvas id="c-cyc"></canvas></div></div>
    <div class="card"><h3>Instructions (M)</h3>
      <div class="chart-wrap" style="height:240px;"><canvas id="c-ins"></canvas></div></div>
  </div>
  <div class="two-col">
    <div class="card"><h3>IPC (instructions/cycle)</h3>
      <div class="chart-wrap" style="height:220px;"><canvas id="c-ipc"></canvas></div></div>
    <div class="card"><h3>Cache-misses (M)</h3>
      <div class="chart-wrap" style="height:220px;"><canvas id="c-cache"></canvas></div></div>
  </div>
</div>

<div class="section" id="sec-tma">
  <div class="card">
    <h3>Analyse Top-Down de Yasin — répartition des slots pipeline</h3>
    <div class="chart-wrap" style="height:280px;"><canvas id="c-tma"></canvas></div>
  </div>
  <div class="tma-grid" id="tmaCards"></div>
</div>

<div class="section" id="sec-versions">
  <div class="controls">
    <label style="font-size:12px;color:#666;">Filtre :</label>
    <select onchange="filterVer(this.value)">
      <option value="all">Toutes</option>
      <option value="ref">Référence</option>
      <option value="good">Bonnes (sans AVX)</option>
      <option value="best">Meilleures (AVX/FMA/OMP)</option>
      <option value="base">Moins bonnes</option>
    </select>
  </div>
  <div class="card" style="padding:0;">
    <table>
      <thead><tr>
        <th>Version</th><th>Signature</th><th>Technique</th>
        <th>Cycles O2 (N=1000)</th><th>Cycles O3</th>
        <th>Gain vs v001</th><th>Catégorie</th>
      </tr></thead>
      <tbody id="tbVer"></tbody>
    </table>
  </div>
</div>

</div>

<script>
{data_js}

function show(id, btn) {{
  document.querySelectorAll('.section').forEach(s => s.classList.remove('active'));
  document.querySelectorAll('.nav button').forEach(b => b.classList.remove('active'));
  document.getElementById('sec-'+id).classList.add('active');
  btn.classList.add('active');
}}

function fmt(n) {{
  if(n>=1e9) return (n/1e9).toFixed(2)+' G';
  if(n>=1e6) return (n/1e6).toFixed(0)+' M';
  return n;
}}

const COLORS = {{
  ref:'#c0392b', good:'#2980b9', best:'#27ae60', base:'#95a5a6'
}};

// Metric cards
const lastIdx = SIZES.length - 1;
const ref_v = VERSIONS[0].data[lastIdx];
const best_v = VERSIONS.reduce((a,b) => a.data[lastIdx] < b.data[lastIdx] ? a : b);
document.getElementById('metricCards').innerHTML = `
  <div class="metric"><div class="lbl">Meilleure version</div>
    <div class="val" style="font-size:18px;">${{best_v.name}}</div>
    <div class="sub">${{best_v.tech}}</div></div>
  <div class="metric"><div class="lbl">Gain maximal</div>
    <div class="val" style="color:#27ae60;">×${{best_v.gain}}</div>
    <div class="sub">vs v001-O2 à N=${{SIZES[lastIdx]}}</div></div>
  <div class="metric"><div class="lbl">Versions analysées</div>
    <div class="val">${{VERSIONS.length}}</div>
    <div class="sub">v001 → v011 (O2 + O3)</div></div>
  <div class="metric"><div class="lbl">Tailles testées</div>
    <div class="val">${{SIZES.length}}</div>
    <div class="sub">N = ${{SIZES.join(', ')}}</div></div>
`;

// Overview bar chart (O2 only, last size)
const o2vers = VERSIONS.filter((_,i) => i%2===0);
new Chart(document.getElementById('c-overview'), {{
  type:'bar',
  data:{{
    labels: o2vers.map(v=>v.name),
    datasets:[{{ label:'Cycles', data:o2vers.map(v=>v.data[lastIdx]),
      backgroundColor: o2vers.map(v=>COLORS[v.cat]) }}]
  }},
  options:{{ responsive:true, maintainAspectRatio:false,
    plugins:{{legend:{{display:false}}}},
    scales:{{
      x:{{ticks:{{font:{{size:10}}}}}},
      y:{{ticks:{{callback:v=>(v/1e9).toFixed(1)+'G'}},
         title:{{display:true,text:'Cycles'}}}}
    }}
  }}
}});

// Progression line chart
const lineColors = ['#e74c3c','#2980b9','#e67e22','#f39c12',
                    '#1abc9c','#27ae60','#8e44ad','#d35400',
                    '#2c3e50','#16a085','#c0392b'];
new Chart(document.getElementById('c-prog'), {{
  type:'line',
  data:{{
    labels: SIZES,
    datasets: o2vers.map((v,i)=>({{
      label:v.name, data:v.data,
      borderColor:lineColors[i%lineColors.length],
      backgroundColor:'transparent', pointRadius:4,
      borderWidth:v.cat==='best'?2.5:1.5
    }}))
  }},
  options:{{ responsive:true, maintainAspectRatio:false,
    plugins:{{legend:{{position:'right',labels:{{font:{{size:10}},boxWidth:12}}}}}},
    scales:{{
      x:{{title:{{display:true,text:'Taille N'}}}},
      y:{{ticks:{{callback:v=>(v/1e9).toFixed(1)+'G'}},
         title:{{display:true,text:'Cycles'}}}}
    }}
  }}
}});

// Zoom (sans v001)
const zoomVers = o2vers.filter(v=>v.cat!=='ref');
new Chart(document.getElementById('c-zoom'), {{
  type:'line',
  data:{{
    labels: SIZES,
    datasets: zoomVers.map((v,i)=>({{
      label:v.name, data:v.data,
      borderColor:lineColors[i%lineColors.length],
      backgroundColor:'transparent', pointRadius:4,
      borderWidth:v.cat==='best'?2.5:1.5
    }}))
  }},
  options:{{ responsive:true, maintainAspectRatio:false,
    plugins:{{legend:{{position:'right',labels:{{font:{{size:10}},boxWidth:12}}}}}},
    scales:{{
      x:{{title:{{display:true,text:'Taille N'}}}},
      y:{{ticks:{{callback:v=>(v/1e9).toFixed(2)+'G'}},
         title:{{display:true,text:'Cycles'}}}}
    }}
  }}
}});

// Perf stat
const pv = ['v001-O2','v002-O2','v007-O2','v008-O2','v009-O2','v006-O2'];
const pc = [8466,745,1240,1039,839,450];
const pi = [10083,2326,3991,2553,3020,1099];
const pp = [1.19,3.12,3.22,2.46,3.60,2.44];
const pm = [64,0.3,0,0,0,27];
const pcols = ['#c0392b','#2980b9','#d35400','#7f8c8d','#2c3e50','#27ae60'];

[['c-cyc',pc,'Cycles (M)'],['c-ins',pi,'Instructions (M)']].forEach(([id,dat,lbl])=>{{
  new Chart(document.getElementById(id),{{type:'bar',
    data:{{labels:pv,datasets:[{{data:dat,backgroundColor:pcols}}]}},
    options:{{responsive:true,maintainAspectRatio:false,
      plugins:{{legend:{{display:false}}}},
      scales:{{x:{{ticks:{{font:{{size:10}}}}}},
               y:{{title:{{display:true,text:lbl}}}}}}}}
  }});
}});
new Chart(document.getElementById('c-ipc'),{{type:'bar',
  data:{{labels:pv,datasets:[{{data:pp,backgroundColor:pcols}}]}},
  options:{{responsive:true,maintainAspectRatio:false,
    plugins:{{legend:{{display:false}}}},
    scales:{{x:{{ticks:{{font:{{size:10}}}}}},y:{{max:4,title:{{display:true,text:'IPC'}}}}}}
  }}
}});
new Chart(document.getElementById('c-cache'),{{type:'bar',
  data:{{labels:pv,datasets:[{{data:pm,backgroundColor:pcols}}]}},
  options:{{responsive:true,maintainAspectRatio:false,
    plugins:{{legend:{{display:false}}}},
    scales:{{x:{{ticks:{{font:{{size:10}}}}}},y:{{title:{{display:true,text:'M misses'}}}}}}
  }}
}});

// TMA
const tmaData = [
  {{ver:'v001-O2',r:52.5,fe:3.2,bs:0.7,be:43.6,bn:'Backend Bound'}},
  {{ver:'v002-O2',r:100,fe:6.7,bs:2.7,be:0,bn:'Retiring'}},
  {{ver:'v006-O2',r:100,fe:20.0,bs:3.0,be:0,bn:'Frontend Bound'}},
  {{ver:'v010-O2',r:100,fe:18.1,bs:3.0,be:0,bn:'Frontend Bound'}},
  {{ver:'v011-O2',r:82.1,fe:12.0,bs:0.5,be:7.0,bn:'Retiring'}},
]
new Chart(document.getElementById('c-tma'),{{type:'bar',
  data:{{labels:tmaData.map(d=>d.ver),datasets:[
    {{label:'Retiring',      data:tmaData.map(d=>d.r),  backgroundColor:'#3266ad'}},
    {{label:'Frontend Bound',data:tmaData.map(d=>d.fe), backgroundColor:'#d4a017'}},
    {{label:'Bad Spec',      data:tmaData.map(d=>d.bs), backgroundColor:'#c0392b'}},
    {{label:'Backend Bound', data:tmaData.map(d=>d.be), backgroundColor:'#27ae60'}},
  ]}},
  options:{{responsive:true,maintainAspectRatio:false,
    plugins:{{legend:{{position:'top',labels:{{font:{{size:11}}}}}}}},
    scales:{{x:{{stacked:true}},y:{{stacked:true,max:100,
      ticks:{{callback:v=>v+'%'}}}}}}
  }}
}});

const tmaCards = document.getElementById('tmaCards');
const tmaColors2 = ['#3266ad','#d4a017','#c0392b','#27ae60'];
tmaData.forEach(d=>{{
  const bars=[['Retiring',d.r],['FE Bound',d.fe],['Bad Spec',d.bs],['BE Bound',d.be]];
  tmaCards.innerHTML+=`<div class="tma-card">
    <h4>${{d.ver}} — <span style="color:#666;font-weight:400;">${{d.bn}}</span></h4>
    ${{bars.map((b,i)=>`<div class="bar-row">
      <div class="bar-lbl">${{b[0]}}</div>
      <div class="bar-track"><div class="bar-fill" style="width:${{Math.min(b[1],100)}}%;background:${{tmaColors2[i]}};"></div></div>
      <div class="bar-val" style="color:${{tmaColors2[i]}};">${{b[1].toFixed(1)}}%</div>
    </div>`).join('')}}
  </div>`;
}});

// Versions table
const tbVer = document.getElementById('tbVer');
const o3vers = VERSIONS.filter((_,i)=>i%2===1);
o2vers.forEach((v,i)=>{{
  const o3 = o3vers[i];
  const badge = v.cat==='best'?'<span class="badge badge-best">AVX/FMA</span>':
                v.cat==='good'?'<span class="badge badge-good">optimisé</span>':
                v.cat==='ref'? '<span class="badge badge-ref">référence</span>':
                '<span class="badge badge-base">base</span>';
  const cls = v.cat==='best'?'best-row':'';
  tbVer.innerHTML+=`<tr class="${{cls}}" data-cat="${{v.cat}}">
    <td><b>${{v.name}}</b></td>
    <td style="font-family:monospace;font-size:11px;">${{v.sig}}</td>
    <td>${{v.tech}}</td>
    <td>${{fmt(v.data[lastIdx])}}</td>
    <td>${{o3?fmt(o3.data[lastIdx]):'—'}}</td>
    <td style="font-weight:600;color:#27ae60;">×${{v.gain}}</td>
    <td>${{badge}}</td>
  </tr>`;
}});

function filterVer(cat){{
  document.querySelectorAll('#tbVer tr').forEach(r=>{{
    r.style.display=(cat==='all'||r.dataset.cat===cat)?'':'none';
  }});
}}
</script>
</body>
</html>"""

os.makedirs(os.path.dirname(output), exist_ok=True)
with open(output, 'w') as f:
    f.write(html)
print(f"Dashboard generated: {output}")
