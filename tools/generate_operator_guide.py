from __future__ import annotations

from datetime import datetime
from pathlib import Path
from typing import Iterable, Sequence

from PIL import Image, ImageDraw, ImageFont
from docx import Document
from docx.enum.section import WD_SECTION
from docx.enum.style import WD_STYLE_TYPE
from docx.enum.table import WD_ALIGN_VERTICAL, WD_TABLE_ALIGNMENT
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK, WD_LINE_SPACING
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Inches, Pt, RGBColor


ROOT = Path(__file__).resolve().parents[1]
DOCS = ROOT / "docs"
ASSETS = DOCS / "assets" / "operator-guide"
CROPS = ASSETS / "crops"
RESOURCE = DOCS / "resource"
OUTPUT = DOCS / "Delta-X-Multi-Robot-Installation-Calibration-Operation-Guide.docx"

PRESET = {
    "name": "compact_reference_guide",
    "page_width": 8.5,
    "page_height": 11.0,
    "margin": 1.0,
    "header_distance": 0.492,
    "footer_distance": 0.492,
    "content_width_dxa": 9360,
    "table_indent_dxa": 120,
    "cell_margins": {"top": 80, "bottom": 80, "start": 120, "end": 120},
    "body_font": "Calibri",
    "body_size": 11,
    "body_after": 6,
    "body_line": 1.25,
    "h1": {"size": 16, "color": "2E74B5", "before": 18, "after": 10},
    "h2": {"size": 13, "color": "2E74B5", "before": 14, "after": 7},
    "h3": {"size": 12, "color": "1F4D78", "before": 10, "after": 5},
    "list_marker_dxa": 269,
    "list_text_dxa": 540,
    "list_hanging_dxa": 271,
    "list_after": 4,
    "list_line": 1.25,
    "table_header_fill": "E8EEF5",
}

COLORS = {
    "navy": "0B2545",
    "blue": "2E74B5",
    "dark_blue": "1F4D78",
    "cyan": "21B6D7",
    "green": "0F766E",
    "gold": "B7791F",
    "red": "9B1C1C",
    "orange": "C05621",
    "ink": "20262E",
    "muted": "5B6573",
    "line": "D8DEE8",
    "light_blue": "E8EEF5",
    "light_gray": "F2F4F7",
    "callout": "F4F6F9",
    "warning": "FFF4E5",
    "danger": "FDECEC",
    "success": "E8F5F2",
}


def color(hex_value: str) -> RGBColor:
    return RGBColor.from_string(hex_value)


def set_run_font(run, name="Calibri", size=None, color_hex=None, bold=None, italic=None):
    run.font.name = name
    run._element.get_or_add_rPr().rFonts.set(qn("w:ascii"), name)
    run._element.get_or_add_rPr().rFonts.set(qn("w:hAnsi"), name)
    run._element.get_or_add_rPr().rFonts.set(qn("w:eastAsia"), name)
    if size is not None:
        run.font.size = Pt(size)
    if color_hex:
        run.font.color.rgb = color(color_hex)
    if bold is not None:
        run.bold = bold
    if italic is not None:
        run.italic = italic


def set_repeat_table_header(row):
    tr_pr = row._tr.get_or_add_trPr()
    tbl_header = OxmlElement("w:tblHeader")
    tbl_header.set(qn("w:val"), "true")
    tr_pr.append(tbl_header)


def set_cell_shading(cell, fill: str):
    tc_pr = cell._tc.get_or_add_tcPr()
    shd = tc_pr.find(qn("w:shd"))
    if shd is None:
        shd = OxmlElement("w:shd")
        tc_pr.append(shd)
    shd.set(qn("w:fill"), fill)
    shd.set(qn("w:val"), "clear")


def set_cell_margins(cell, top=80, start=120, bottom=80, end=120):
    tc_pr = cell._tc.get_or_add_tcPr()
    tc_mar = tc_pr.find(qn("w:tcMar"))
    if tc_mar is None:
        tc_mar = OxmlElement("w:tcMar")
        tc_pr.append(tc_mar)
    for side, value in (("top", top), ("start", start), ("bottom", bottom), ("end", end)):
        node = tc_mar.find(qn(f"w:{side}"))
        if node is None:
            node = OxmlElement(f"w:{side}")
            tc_mar.append(node)
        node.set(qn("w:w"), str(value))
        node.set(qn("w:type"), "dxa")


def set_cell_width(cell, width_dxa: int):
    tc_pr = cell._tc.get_or_add_tcPr()
    tc_w = tc_pr.find(qn("w:tcW"))
    if tc_w is None:
        tc_w = OxmlElement("w:tcW")
        tc_pr.append(tc_w)
    tc_w.set(qn("w:w"), str(width_dxa))
    tc_w.set(qn("w:type"), "dxa")


def set_table_geometry(table, widths_dxa: Sequence[int]):
    if sum(widths_dxa) != PRESET["content_width_dxa"]:
        raise ValueError(f"Table widths must total 9360 DXA: {widths_dxa}")
    table.alignment = WD_TABLE_ALIGNMENT.LEFT
    table.autofit = False
    tbl_pr = table._tbl.tblPr

    tbl_w = tbl_pr.find(qn("w:tblW"))
    if tbl_w is None:
        tbl_w = OxmlElement("w:tblW")
        tbl_pr.append(tbl_w)
    tbl_w.set(qn("w:w"), str(PRESET["content_width_dxa"]))
    tbl_w.set(qn("w:type"), "dxa")

    tbl_ind = tbl_pr.find(qn("w:tblInd"))
    if tbl_ind is None:
        tbl_ind = OxmlElement("w:tblInd")
        tbl_pr.append(tbl_ind)
    tbl_ind.set(qn("w:w"), str(PRESET["table_indent_dxa"]))
    tbl_ind.set(qn("w:type"), "dxa")

    layout = tbl_pr.find(qn("w:tblLayout"))
    if layout is None:
        layout = OxmlElement("w:tblLayout")
        tbl_pr.append(layout)
    layout.set(qn("w:type"), "fixed")

    cell_mar = tbl_pr.find(qn("w:tblCellMar"))
    if cell_mar is None:
        cell_mar = OxmlElement("w:tblCellMar")
        tbl_pr.append(cell_mar)
    for side, value in PRESET["cell_margins"].items():
        node = cell_mar.find(qn(f"w:{side}"))
        if node is None:
            node = OxmlElement(f"w:{side}")
            cell_mar.append(node)
        node.set(qn("w:w"), str(value))
        node.set(qn("w:type"), "dxa")

    grid = table._tbl.tblGrid
    for col in list(grid):
        grid.remove(col)
    for width in widths_dxa:
        grid_col = OxmlElement("w:gridCol")
        grid_col.set(qn("w:w"), str(width))
        grid.append(grid_col)

    for row in table.rows:
        for idx, cell in enumerate(row.cells):
            set_cell_width(cell, widths_dxa[idx])
            set_cell_margins(cell, **PRESET["cell_margins"])
            cell.vertical_alignment = WD_ALIGN_VERTICAL.CENTER


def set_paragraph_border_left(paragraph, color_hex: str, size=18, space=8):
    p_pr = paragraph._p.get_or_add_pPr()
    p_bdr = p_pr.find(qn("w:pBdr"))
    if p_bdr is None:
        p_bdr = OxmlElement("w:pBdr")
        p_pr.append(p_bdr)
    left = p_bdr.find(qn("w:left"))
    if left is None:
        left = OxmlElement("w:left")
        p_bdr.append(left)
    left.set(qn("w:val"), "single")
    left.set(qn("w:sz"), str(size))
    left.set(qn("w:space"), str(space))
    left.set(qn("w:color"), color_hex)


def set_paragraph_shading(paragraph, fill: str):
    p_pr = paragraph._p.get_or_add_pPr()
    shd = p_pr.find(qn("w:shd"))
    if shd is None:
        shd = OxmlElement("w:shd")
        p_pr.append(shd)
    shd.set(qn("w:fill"), fill)
    shd.set(qn("w:val"), "clear")


def add_field(run, instruction: str):
    begin = OxmlElement("w:fldChar")
    begin.set(qn("w:fldCharType"), "begin")
    instr = OxmlElement("w:instrText")
    instr.set(qn("xml:space"), "preserve")
    instr.text = instruction
    separate = OxmlElement("w:fldChar")
    separate.set(qn("w:fldCharType"), "separate")
    text = OxmlElement("w:t")
    text.text = "1"
    end = OxmlElement("w:fldChar")
    end.set(qn("w:fldCharType"), "end")
    run._r.extend([begin, instr, separate, text, end])


def add_abstract_numbering(doc: Document, num_fmt: str, level_text: str, bullet_font=None) -> int:
    numbering = doc.part.numbering_part.element
    existing = [
        int(el.get(qn("w:abstractNumId")))
        for el in numbering.findall(qn("w:abstractNum"))
        if el.get(qn("w:abstractNumId")) is not None
    ]
    abstract_id = max(existing, default=-1) + 1
    abstract = OxmlElement("w:abstractNum")
    abstract.set(qn("w:abstractNumId"), str(abstract_id))
    multi = OxmlElement("w:multiLevelType")
    multi.set(qn("w:val"), "singleLevel")
    abstract.append(multi)

    lvl = OxmlElement("w:lvl")
    lvl.set(qn("w:ilvl"), "0")
    start = OxmlElement("w:start")
    start.set(qn("w:val"), "1")
    fmt = OxmlElement("w:numFmt")
    fmt.set(qn("w:val"), num_fmt)
    text = OxmlElement("w:lvlText")
    text.set(qn("w:val"), level_text)
    jc = OxmlElement("w:lvlJc")
    jc.set(qn("w:val"), "left")
    lvl.extend([start, fmt, text, jc])

    p_pr = OxmlElement("w:pPr")
    tabs = OxmlElement("w:tabs")
    tab = OxmlElement("w:tab")
    tab.set(qn("w:val"), "num")
    tab.set(qn("w:pos"), str(PRESET["list_text_dxa"]))
    tabs.append(tab)
    ind = OxmlElement("w:ind")
    ind.set(qn("w:left"), str(PRESET["list_text_dxa"]))
    ind.set(qn("w:hanging"), str(PRESET["list_hanging_dxa"]))
    spacing = OxmlElement("w:spacing")
    spacing.set(qn("w:before"), "0")
    spacing.set(qn("w:after"), str(PRESET["list_after"] * 20))
    spacing.set(qn("w:line"), "300")
    spacing.set(qn("w:lineRule"), "auto")
    p_pr.extend([tabs, ind, spacing])
    lvl.append(p_pr)
    if bullet_font:
        r_pr = OxmlElement("w:rPr")
        fonts = OxmlElement("w:rFonts")
        fonts.set(qn("w:ascii"), bullet_font)
        fonts.set(qn("w:hAnsi"), bullet_font)
        r_pr.append(fonts)
        lvl.append(r_pr)
    abstract.append(lvl)
    numbering.append(abstract)
    return abstract_id


def add_num_instance(doc: Document, abstract_id: int) -> int:
    numbering = doc.part.numbering_part.element
    existing = [
        int(el.get(qn("w:numId")))
        for el in numbering.findall(qn("w:num"))
        if el.get(qn("w:numId")) is not None
    ]
    num_id = max(existing, default=0) + 1
    num = OxmlElement("w:num")
    num.set(qn("w:numId"), str(num_id))
    abstract_ref = OxmlElement("w:abstractNumId")
    abstract_ref.set(qn("w:val"), str(abstract_id))
    num.append(abstract_ref)
    numbering.append(num)
    return num_id


def apply_num(paragraph, num_id: int):
    p_pr = paragraph._p.get_or_add_pPr()
    num_pr = p_pr.find(qn("w:numPr"))
    if num_pr is None:
        num_pr = OxmlElement("w:numPr")
        p_pr.append(num_pr)
    ilvl = OxmlElement("w:ilvl")
    ilvl.set(qn("w:val"), "0")
    num_id_node = OxmlElement("w:numId")
    num_id_node.set(qn("w:val"), str(num_id))
    num_pr.extend([ilvl, num_id_node])


def configure_styles(doc: Document):
    normal = doc.styles["Normal"]
    normal.font.name = PRESET["body_font"]
    normal._element.rPr.rFonts.set(qn("w:ascii"), PRESET["body_font"])
    normal._element.rPr.rFonts.set(qn("w:hAnsi"), PRESET["body_font"])
    normal._element.rPr.rFonts.set(qn("w:eastAsia"), PRESET["body_font"])
    normal.font.size = Pt(PRESET["body_size"])
    normal.font.color.rgb = color(COLORS["ink"])
    normal.paragraph_format.space_before = Pt(0)
    normal.paragraph_format.space_after = Pt(PRESET["body_after"])
    normal.paragraph_format.line_spacing = PRESET["body_line"]

    for style_name, tokens in (("Heading 1", PRESET["h1"]), ("Heading 2", PRESET["h2"]), ("Heading 3", PRESET["h3"])):
        style = doc.styles[style_name]
        style.font.name = PRESET["body_font"]
        style._element.rPr.rFonts.set(qn("w:ascii"), PRESET["body_font"])
        style._element.rPr.rFonts.set(qn("w:hAnsi"), PRESET["body_font"])
        style._element.rPr.rFonts.set(qn("w:eastAsia"), PRESET["body_font"])
        style.font.size = Pt(tokens["size"])
        style.font.color.rgb = color(tokens["color"])
        style.font.bold = True
        style.paragraph_format.space_before = Pt(tokens["before"])
        style.paragraph_format.space_after = Pt(tokens["after"])
        style.paragraph_format.line_spacing = 1.0
        style.paragraph_format.keep_with_next = True

    caption = doc.styles["Caption"]
    caption.font.name = PRESET["body_font"]
    caption._element.rPr.rFonts.set(qn("w:ascii"), PRESET["body_font"])
    caption._element.rPr.rFonts.set(qn("w:hAnsi"), PRESET["body_font"])
    caption.font.size = Pt(9)
    caption.font.color.rgb = color(COLORS["muted"])
    caption.font.italic = True
    caption.paragraph_format.space_before = Pt(3)
    caption.paragraph_format.space_after = Pt(8)
    caption.paragraph_format.line_spacing = 1.0

    code_style = doc.styles.add_style("Code Block", WD_STYLE_TYPE.PARAGRAPH)
    code_style.base_style = doc.styles["Normal"]
    code_style.font.name = "Consolas"
    code_style._element.rPr.rFonts.set(qn("w:ascii"), "Consolas")
    code_style._element.rPr.rFonts.set(qn("w:hAnsi"), "Consolas")
    code_style.font.size = Pt(8.5)
    code_style.font.color.rgb = color(COLORS["navy"])
    code_style.paragraph_format.left_indent = Inches(0.15)
    code_style.paragraph_format.right_indent = Inches(0.10)
    code_style.paragraph_format.space_before = Pt(4)
    code_style.paragraph_format.space_after = Pt(8)
    code_style.paragraph_format.line_spacing = 1.0


def configure_section(section):
    section.page_width = Inches(PRESET["page_width"])
    section.page_height = Inches(PRESET["page_height"])
    section.top_margin = Inches(PRESET["margin"])
    section.bottom_margin = Inches(PRESET["margin"])
    section.left_margin = Inches(PRESET["margin"])
    section.right_margin = Inches(PRESET["margin"])
    section.header_distance = Inches(PRESET["header_distance"])
    section.footer_distance = Inches(PRESET["footer_distance"])
    section.different_first_page_header_footer = True


def configure_headers(section):
    header = section.header
    p = header.paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.LEFT
    p.paragraph_format.space_after = Pt(3)
    run = p.add_run("DELTA X SOFTWARE  |  MULTI-ROBOT CONVEYOR SORTING")
    set_run_font(run, size=8.5, color_hex=COLORS["muted"], bold=True)
    p_pr = p._p.get_or_add_pPr()
    p_bdr = OxmlElement("w:pBdr")
    bottom = OxmlElement("w:bottom")
    bottom.set(qn("w:val"), "single")
    bottom.set(qn("w:sz"), "4")
    bottom.set(qn("w:space"), "4")
    bottom.set(qn("w:color"), COLORS["line"])
    p_bdr.append(bottom)
    p_pr.append(p_bdr)

    first_header = section.first_page_header
    first_header.paragraphs[0].clear()

    footer = section.footer
    fp = footer.paragraphs[0]
    fp.alignment = WD_ALIGN_PARAGRAPH.RIGHT
    fp.paragraph_format.space_before = Pt(3)
    r = fp.add_run("Trang ")
    set_run_font(r, size=8.5, color_hex=COLORS["muted"])
    r2 = fp.add_run()
    set_run_font(r2, size=8.5, color_hex=COLORS["muted"])
    add_field(r2, "PAGE")
    r3 = fp.add_run(" / ")
    set_run_font(r3, size=8.5, color_hex=COLORS["muted"])
    r4 = fp.add_run()
    set_run_font(r4, size=8.5, color_hex=COLORS["muted"])
    add_field(r4, "NUMPAGES")

    first_footer = section.first_page_footer
    ffp = first_footer.paragraphs[0]
    ffp.alignment = WD_ALIGN_PARAGRAPH.CENTER
    fr = ffp.add_run("Commissioning guide - Revision 0.2 - 2026-08-24")
    set_run_font(fr, size=8.5, color_hex=COLORS["muted"])


def add_body(doc, text: str, bold_prefix: str | None = None, italic=False, after=None):
    p = doc.add_paragraph()
    if bold_prefix and text.startswith(bold_prefix):
        r1 = p.add_run(bold_prefix)
        set_run_font(r1, bold=True)
        r2 = p.add_run(text[len(bold_prefix):])
        set_run_font(r2, italic=italic)
    else:
        r = p.add_run(text)
        set_run_font(r, italic=italic)
    if after is not None:
        p.paragraph_format.space_after = Pt(after)
    return p


def add_bullets(doc, items: Iterable[str], bullet_num_id: int):
    for item in items:
        p = doc.add_paragraph()
        apply_num(p, bullet_num_id)
        set_run_font(p.add_run(item))


def add_steps(doc, items: Iterable[str], decimal_abstract_id: int):
    num_id = add_num_instance(doc, decimal_abstract_id)
    for item in items:
        p = doc.add_paragraph()
        apply_num(p, num_id)
        set_run_font(p.add_run(item))


def add_callout(doc, label: str, text: str, kind="info"):
    fill, accent = {
        "info": (COLORS["callout"], COLORS["blue"]),
        "warning": (COLORS["warning"], COLORS["gold"]),
        "danger": (COLORS["danger"], COLORS["red"]),
        "success": (COLORS["success"], COLORS["green"]),
    }[kind]
    p = doc.add_paragraph()
    p.paragraph_format.left_indent = Inches(0.12)
    p.paragraph_format.right_indent = Inches(0.08)
    p.paragraph_format.space_before = Pt(5)
    p.paragraph_format.space_after = Pt(8)
    p.paragraph_format.line_spacing = 1.15
    set_paragraph_shading(p, fill)
    set_paragraph_border_left(p, accent)
    r1 = p.add_run(f"{label}: ")
    set_run_font(r1, bold=True, color_hex=accent)
    r2 = p.add_run(text)
    set_run_font(r2)
    return p


def add_table(doc, headers: Sequence[str], rows: Sequence[Sequence[str]], widths_dxa: Sequence[int]):
    table = doc.add_table(rows=1, cols=len(headers))
    table.style = "Table Grid"
    for idx, header in enumerate(headers):
        cell = table.rows[0].cells[idx]
        set_cell_shading(cell, PRESET["table_header_fill"])
        p = cell.paragraphs[0]
        p.alignment = WD_ALIGN_PARAGRAPH.CENTER
        p.paragraph_format.space_before = Pt(0)
        p.paragraph_format.space_after = Pt(0)
        p.paragraph_format.line_spacing = 1.0
        set_run_font(p.add_run(header), size=9.5, bold=True, color_hex=COLORS["navy"])
    set_repeat_table_header(table.rows[0])
    for row_data in rows:
        row = table.add_row()
        for idx, value in enumerate(row_data):
            cell = row.cells[idx]
            p = cell.paragraphs[0]
            p.paragraph_format.space_before = Pt(0)
            p.paragraph_format.space_after = Pt(0)
            p.paragraph_format.line_spacing = 1.05
            p.alignment = WD_ALIGN_PARAGRAPH.CENTER if idx == 0 and len(headers) > 2 else WD_ALIGN_PARAGRAPH.LEFT
            set_run_font(p.add_run(str(value)), size=9.3)
    set_table_geometry(table, widths_dxa)
    doc.add_paragraph().paragraph_format.space_after = Pt(2)
    return table


def add_image(doc, image_path: Path, caption: str, width=6.2):
    if not image_path.exists():
        raise FileNotFoundError(image_path)
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_before = Pt(4)
    p.paragraph_format.space_after = Pt(0)
    p.paragraph_format.keep_with_next = True
    run = p.add_run()
    shape = run.add_picture(str(image_path), width=Inches(width))
    shape._inline.docPr.set("descr", caption)
    shape._inline.docPr.set("title", caption)
    cap = doc.add_paragraph(style="Caption")
    cap.alignment = WD_ALIGN_PARAGRAPH.CENTER
    set_run_font(cap.add_run(caption), size=9, color_hex=COLORS["muted"], italic=True)
    return shape


def add_code(doc, code_text: str):
    p = doc.add_paragraph(style="Code Block")
    set_paragraph_shading(p, COLORS["light_gray"])
    set_paragraph_border_left(p, COLORS["blue"], size=12, space=6)
    run = p.add_run(code_text.rstrip())
    set_run_font(run, name="Consolas", size=8.5, color_hex=COLORS["navy"])
    return p


def page_break(doc):
    doc.add_paragraph().add_run().add_break(WD_BREAK.PAGE)


def section_heading(doc, title: str, first=False):
    if not first:
        page_break(doc)
    p = doc.add_paragraph(title, style="Heading 1")
    p.paragraph_format.space_before = Pt(0)
    return p


def _font(size, bold=False):
    candidates = [
        Path("C:/Windows/Fonts/segoeui.ttf"),
        Path("C:/Windows/Fonts/arial.ttf"),
    ]
    if bold:
        candidates = [Path("C:/Windows/Fonts/seguisb.ttf"), Path("C:/Windows/Fonts/arialbd.ttf")] + candidates
    for candidate in candidates:
        if candidate.exists():
            return ImageFont.truetype(str(candidate), size)
    return ImageFont.load_default()


def fit_text(draw, text, box_width, max_size=34, min_size=18, bold=False):
    for size in range(max_size, min_size - 1, -1):
        font = _font(size, bold)
        if draw.textbbox((0, 0), text, font=font)[2] <= box_width:
            return font
    return _font(min_size, bold)


def draw_centered(draw, box, text, font, fill):
    x1, y1, x2, y2 = box
    bbox = draw.multiline_textbbox((0, 0), text, font=font, spacing=5, align="center")
    w, h = bbox[2] - bbox[0], bbox[3] - bbox[1]
    draw.multiline_text(((x1 + x2 - w) / 2, (y1 + y2 - h) / 2), text, font=font, fill=fill, spacing=5, align="center")


def create_architecture_diagram(path: Path):
    canvas = Image.new("RGB", (1800, 980), "#FFFFFF")
    d = ImageDraw.Draw(canvas)
    title = _font(42, True)
    label = _font(28, True)
    body = _font(24)
    d.text((70, 45), "Data Flow and Coordinate Systems", font=title, fill="#0B2545")

    boxes = [
        ((70, 170, 370, 350), "CAMERA\nUSB / GigE", "#E8F5F2", "#0F766E"),
        ((450, 170, 750, 350), "DETECTOR\ntype, x, y, w, h, angle", "#E8EEF5", "#2E74B5"),
        ((830, 170, 1130, 350), "MAPPING\nP (pixel) -> C (mm)", "#FFF4E5", "#B7791F"),
        ((1210, 170, 1720, 350), "TRACKING + ENCODER\nUID, pose, velocity, stale", "#F4F6F9", "#1F4D78"),
        ((530, 470, 1260, 650), "SHARED OBJECT MAP\nclaim(owner, lease) -> complete / release", "#FDECEC", "#9B1C1C"),
        ((140, 770, 520, 920), "ROBOT 0\nC -> R0, zone 0, type 0", "#E8EEF5", "#2E74B5"),
        ((710, 770, 1090, 920), "ROBOT 1\nC -> R1, zone 1, type 1", "#E8F5F2", "#0F766E"),
        ((1280, 770, 1660, 920), "ROBOT N\nC -> RN, rule N", "#FFF4E5", "#B7791F"),
    ]
    for rect, text, fill, outline in boxes:
        d.rounded_rectangle(rect, radius=20, fill=fill, outline=outline, width=5)
        draw_centered(d, rect, text, fit_text(d, max(text.split("\n"), key=len), rect[2] - rect[0] - 40, 30, 20, True), "#20262E")

    def arrow(x1, y1, x2, y2, color_hex="#5B6573"):
        d.line((x1, y1, x2, y2), fill=color_hex, width=8)
        import math
        angle = math.atan2(y2 - y1, x2 - x1)
        size = 22
        p1 = (x2 - size * math.cos(angle - 0.55), y2 - size * math.sin(angle - 0.55))
        p2 = (x2 - size * math.cos(angle + 0.55), y2 - size * math.sin(angle + 0.55))
        d.polygon([(x2, y2), p1, p2], fill=color_hex)

    arrow(370, 260, 450, 260)
    arrow(750, 260, 830, 260)
    arrow(1130, 260, 1210, 260)
    arrow(1465, 350, 1120, 470)
    arrow(760, 650, 330, 770)
    arrow(895, 650, 900, 770)
    arrow(1030, 650, 1470, 770)
    d.text((75, 390), "P: camera pixels   |   C: conveyor (mm)   |   Ri: robot i coordinates", font=body, fill="#5B6573")
    canvas.save(path, quality=95)


def create_state_diagram(path: Path):
    canvas = Image.new("RGB", (1800, 760), "#FFFFFF")
    d = ImageDraw.Draw(canvas)
    title = _font(40, True)
    label = _font(28, True)
    small = _font(22)
    d.text((70, 45), "Object Lifecycle in Shared Tracking", font=title, fill="#0B2545")
    states = [
        (90, "DETECTED", "detector returns\ntype + pose"),
        (440, "TRACKED", "UID + encoder\ncompensation"),
        (790, "CLAIMED", "owner + lease"),
        (1140, "PICKING", "G01 ... SYNC"),
        (1490, "COMPLETED", "not claimable\nagain"),
    ]
    y1, y2 = 250, 430
    for x, name, desc in states:
        rect = (x, y1, x + 250, y2)
        fill = "#E8EEF5" if name not in ("CLAIMED", "COMPLETED") else ("#FFF4E5" if name == "CLAIMED" else "#E8F5F2")
        outline = "#2E74B5" if name not in ("CLAIMED", "COMPLETED") else ("#B7791F" if name == "CLAIMED" else "#0F766E")
        d.rounded_rectangle(rect, radius=18, fill=fill, outline=outline, width=5)
        bbox = d.textbbox((0, 0), name, font=label)
        d.text((x + (250 - (bbox[2] - bbox[0])) / 2, y1 + 35), name, font=label, fill="#20262E")
        d.multiline_text((x + 20, y1 + 95), desc, font=small, fill="#5B6573", spacing=4, align="center")
        if x < 1490:
            d.line((x + 250, 340, x + 330, 340), fill="#5B6573", width=7)
            d.polygon([(x + 330, 340), (x + 305, 325), (x + 305, 355)], fill="#5B6573")

    d.rounded_rectangle((720, 550, 1110, 690), radius=18, fill="#FDECEC", outline="#9B1C1C", width=4)
    draw_centered(d, (720, 550, 1110, 690), "releaseObject or lease expiry\n-> return to TRACKED", small, "#20262E")
    d.line((915, 430, 915, 550), fill="#9B1C1C", width=6)
    d.polygon([(915, 550), (900, 525), (930, 525)], fill="#9B1C1C")
    d.line((720, 620, 565, 455), fill="#9B1C1C", width=6)
    d.polygon([(565, 455), (588, 468), (575, 488)], fill="#9B1C1C")
    canvas.save(path, quality=95)


def crop_images():
    CROPS.mkdir(parents=True, exist_ok=True)
    crops = {
        "camera_calibration.png": ("02_camera_calibration.png", (65, 115, 1840, 1070)),
        "mapping_detector.png": ("03_mapping_detector.png", (65, 110, 1840, 1070)),
        "detector_thresholds.png": ("04_detector_tracking_thresholds.png", (65, 110, 1840, 1070)),
        "tracking_table.png": ("05_tracking_object_table.png", (65, 110, 1840, 1070)),
        "point_tool.png": ("06_point_tool_tracking_matrix.png", (65, 110, 1840, 1060)),
        "conveyor_panel.png": ("07_conveyor_setup.png", (1840, 80, 2740, 430)),
        "encoder_panel.png": ("08_encoder_setup_scheduler.png", (1840, 80, 2740, 440)),
        "vision_script.png": ("09_gscript_vision_loop.png", (65, 115, 1835, 845)),
        "worker_script.png": ("10_gscript_robot_worker.png", (65, 115, 1835, 845)),
        "robot_panel.png": ("11_robot_setup_jogging.png", (1840, 80, 2740, 770)),
        "device_settings.png": ("12_settings_device.png", (65, 65, 1500, 540)),
    }
    for output_name, (source_name, box) in crops.items():
        source = ASSETS / source_name
        if not source.exists():
            continue
        with Image.open(source) as img:
            img.crop(box).save(CROPS / output_name, quality=95)


def add_cover(doc: Document):
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_after = Pt(30)
    logo = ROOT / "icon" / "logo.png"
    shape = p.add_run().add_picture(str(logo), width=Inches(1.05))
    shape._inline.docPr.set("descr", "Delta X Software logo")

    kicker = doc.add_paragraph()
    kicker.alignment = WD_ALIGN_PARAGRAPH.CENTER
    kicker.paragraph_format.space_before = Pt(24)
    kicker.paragraph_format.space_after = Pt(14)
    set_run_font(kicker.add_run("COMMISSIONING AND OPERATIONS MANUAL"), size=11, bold=True, color_hex=COLORS["gold"])

    title = doc.add_paragraph()
    title.alignment = WD_ALIGN_PARAGRAPH.CENTER
    title.paragraph_format.space_after = Pt(10)
    set_run_font(title.add_run("Installation, Calibration,\nand Operation Guide"), size=29, bold=True, color_hex=COLORS["navy"])

    subtitle = doc.add_paragraph()
    subtitle.alignment = WD_ALIGN_PARAGRAPH.CENTER
    subtitle.paragraph_format.space_after = Pt(28)
    set_run_font(subtitle.add_run("Delta X Software - Multi-Robot Sorting on a Shared Conveyor"), size=15, color_hex=COLORS["dark_blue"])

    rule = doc.add_paragraph()
    rule.paragraph_format.space_after = Pt(28)
    p_pr = rule._p.get_or_add_pPr()
    p_bdr = OxmlElement("w:pBdr")
    bottom = OxmlElement("w:bottom")
    bottom.set(qn("w:val"), "single")
    bottom.set(qn("w:sz"), "12")
    bottom.set(qn("w:space"), "1")
    bottom.set(qn("w:color"), COLORS["cyan"])
    p_bdr.append(bottom)
    p_pr.append(p_bdr)

    meta = doc.add_paragraph()
    meta.alignment = WD_ALIGN_PARAGRAPH.CENTER
    meta.paragraph_format.space_after = Pt(5)
    set_run_font(meta.add_run("Applies to Delta X Software 2.0.0 and the multi-robot tracking platform"), size=10.5, bold=True, color_hex=COLORS["muted"])
    meta2 = doc.add_paragraph()
    meta2.alignment = WD_ALIGN_PARAGRAPH.CENTER
    set_run_font(meta2.add_run("Audience: system integrators, commissioning engineers, and lead operators"), size=9.5, italic=True, color_hex=COLORS["muted"])


def build_document():
    ASSETS.mkdir(parents=True, exist_ok=True)
    create_architecture_diagram(ASSETS / "system_architecture.png")
    create_state_diagram(ASSETS / "object_state_flow.png")
    crop_images()

    doc = Document()
    configure_styles(doc)
    section = doc.sections[0]
    configure_section(section)
    configure_headers(section)

    props = doc.core_properties
    props.title = "Delta X Multi-Robot Installation, Calibration, and Operation Guide"
    props.subject = "Commissioning and operating a multi-robot conveyor sorting cell"
    props.author = "Delta X Software"
    props.last_modified_by = "Delta X Software"
    props.comments = f"Preset: {PRESET['name']}; Header: editorial_cover"
    props.created = datetime(2026, 8, 24)
    props.modified = datetime(2026, 8, 24)

    bullet_abs = add_abstract_numbering(doc, "bullet", "•", "Calibri")
    decimal_abs = add_abstract_numbering(doc, "decimal", "%1.")
    bullet_num = add_num_instance(doc, bullet_abs)

    add_cover(doc)
    page_break(doc)

    doc.add_paragraph("Document Control", style="Heading 1")
    add_table(
        doc,
        ["Field", "Value"],
        [
            ["Document", "Delta X Multi-Robot Installation, Calibration, and Operation Guide"],
            ["Revision", "0.2 - Release candidate"],
            ["Date", "2026-08-24"],
            ["Scope", "One camera, one encoder, one conveyor, and multiple delta robots using shared tracking"],
            ["Example assets", "script-example/multi-robot-sorting/"],
        ],
        [2700, 6660],
    )
    add_callout(
        doc,
        "SAFETY",
        "G-Script, vision, and tracking are not safety functions. E-stop, guards, axis limits, end-effector energy isolation, and collision prevention must be implemented by an appropriate safety circuit, PLC, or controller.",
        "danger",
    )
    doc.add_paragraph("How to Use This Guide", style="Heading 2")
    add_bullets(
        doc,
        [
            "System integrators should follow Sections 1 through 9 during initial commissioning.",
            "Operators should use Sections 10 through 12 and the acceptance checklist in Section 13.",
            "Every calibration section has an acceptance gate. Do not proceed until the previous gate passes.",
            "Numeric values in sample programs are starting points and must be replaced with measurements from the actual cell.",
        ],
        bullet_num,
    )
    doc.add_paragraph("Contents", style="Heading 2")
    add_steps(
        doc,
        [
            "System architecture and coordinate conventions",
            "Hardware installation",
            "Software installation",
            "Project and device setup",
            "Encoder calibration",
            "Camera and image-region calibration",
            "Camera P to conveyor C mapping",
            "Conveyor C to robot Ri mapping",
            "Detector and tracking configuration",
            "Multi-robot G-Script configuration",
            "Operation, stopping, and fault recovery",
            "Acceptance and maintenance",
        ],
        decimal_abs,
    )

    section_heading(doc, "1. System Architecture and Coordinate Conventions")
    add_body(doc, "The system uses one shared moving-object map. The camera produces detections; encoder-aware tracking converts detections into stable UIDs; each robot is an independent worker that obtains ownership through an atomic claim.")
    add_image(doc, ASSETS / "system_architecture.png", "Figure 1 - Camera to detector to tracking to shared object map to robot workers", 6.3)
    doc.add_paragraph("Keep three coordinate systems separate", style="Heading 2")
    add_table(
        doc,
        ["System", "Unit", "Convention and use"],
        [
            ["P", "pixel", "Camera coordinates after resize, crop, and warp; used only before mapping."],
            ["C", "mm", "Shared conveyor system; use +Y along belt travel and +X across the belt."],
            ["Ri", "mm/deg", "Robot i local coordinates; every robot G01 move executes in this system."],
        ],
        [900, 1100, 7360],
    )
    add_callout(doc, "RULE", "Define claim zones in C. Only after a successful claim may a worker map the pick point from C to Ri with ConveyorToRobotN.Map(x,y).", "info")
    add_image(doc, ASSETS / "object_state_flow.png", "Figure 2 - UID lifecycle and owner/lease protection against duplicate picks", 6.3)

    section_heading(doc, "2. Hardware Installation")
    doc.add_paragraph("2.1 Recommended mechanical layout", style="Heading 2")
    add_steps(
        doc,
        [
            "Mount the encoder on a non-slip shaft or a measuring wheel with stable pressure. Do not use motor pulses when the transmission may slip relative to the belt.",
            "Place the camera far enough upstream for inference, communication, and robot approach. Rigidly mount camera, lens, and lighting as one assembly.",
            "Install robots in conveyor order. Keep robot workspaces non-overlapping until a collision coordinator is available.",
            "Separate encoder and camera cables from power cables; terminate shielding according to the manufacturer requirements.",
            "Verify that E-stop, guards, mechanical limits, safe torque off, and vacuum release operate independently of the PC.",
        ],
        decimal_abs,
    )
    doc.add_paragraph("2.2 Naming convention", style="Heading 2")
    add_table(
        doc,
        ["Device", "Software name", "Related variable or matrix"],
        [
            ["Camera/detect", "detect0", "tracking0, #Objects"],
            ["Encoder", "encoder0", "tracking0.VelocityVector"],
            ["Conveyor", "conveyor0", "+Y of C"],
            ["First robot", "robot0", "#0.ConveyorToRobot0, #R0..."],
            ["Second robot", "robot1", "#0.ConveyorToRobot1, #R1..."],
        ],
        [1800, 2500, 5060],
    )
    add_callout(doc, "ACCEPTANCE", "Moving the belt by hand in the production direction increases C.Y. If it does not, reverse the sign in exactly one place.", "success")

    section_heading(doc, "3. Installing Delta X Software")
    doc.add_paragraph("3.1 Windows operator station", style="Heading 2")
    add_bullets(
        doc,
        [
            "Windows 10/11 64-bit and Microsoft Visual C++ Redistributable 2015-2022 x64.",
            "A portable package includes the Qt runtime, OpenCV DLL, GScript_Documentation.html, script-example/, and plugin/. Models and proprietary camera runtimes are installed separately.",
            "Install Basler pylon Runtime or Hikrobot MVS Runtime before using the corresponding GigE/USB3 Vision camera.",
            "Install 64-bit Python when using an external detector or YOLO; use a dedicated virtual environment for the cell.",
        ],
        bullet_num,
    )
    add_code(
        doc,
        "py -3.10 -m venv %LOCALAPPDATA%\\DeltaX\\py\n"
        "%LOCALAPPDATA%\\DeltaX\\py\\Scripts\\pip install ^\n"
        "  ultralytics==8.0.200 opencv-python==4.9.0.80 numpy==1.26.4",
    )
    doc.add_paragraph("3.2 Build from source (development station)", style="Heading 2")
    add_bullets(
        doc,
        [
            "Visual Studio 2022 MSVC v143, workload Desktop development with C++.",
            "Qt 6 for MSVC 2022 x64 with Serial Port, Multimedia, Svg, and Svg Widgets.",
            "Rerun qmake after changing a Qt kit to avoid stale generated ui_*.h files.",
            "Build Release, run windeployqt, and then use the repository packaging script to include verified runtime assets.",
        ],
        bullet_num,
    )
    add_image(doc, CROPS / "device_settings.png", "Figure 3 - Settings > Device: default COM port, baud rate, timeout, and reconnect", 6.3)
    add_callout(doc, "DO NOT SAVE YET", "Do not click Save Settings until COM ports, baud rates, timeout, and the default camera have been verified. Back up settings before a major change.", "warning")

    section_heading(doc, "4. Project and Device Setup")
    add_steps(
        doc,
        [
            "Open Delta X Software, click + to create a project, and save it with an unambiguous cell or line name.",
            "On Robot, add robot0, robot1, and so on; select the controller COM port, baud rate, model, and degrees of freedom.",
            "On Conveyor, add conveyor0 and select direct G-code control or robot output according to the wiring design.",
            "On Encoder, add encoder0, select the X/Y axis, link conveyor0 when required, and enable Active.",
            "In Object Detector, create detect0, select Webcam / Industrial Camera / Images / Socket, and attach tracking0.",
        ],
        decimal_abs,
    )
    add_image(doc, CROPS / "robot_panel.png", "Figure 4 - Robot: connection, homing, pose, jogging, and motion parameters", 5.4)
    add_callout(doc, "JOGGING", "For first motion, use a safe Z, 0.1-1 mm steps, and low speed. Verify X/Y/Z/W signs before homing or running a program.", "danger")
    add_image(doc, CROPS / "conveyor_panel.png", "Figure 5 - Conveyor: Manual Control mode, speed, distance, and target position", 5.8)
    add_image(doc, CROPS / "encoder_panel.png", "Figure 6 - Encoder: conveyor link, timer, velocity, position, reset, and scheduled G-code", 5.8)

    section_heading(doc, "5. Encoder Calibration")
    add_body(doc, "The encoder is the authoritative source for conveyor travel. Do not replace it with PC-time interpolation: the conveyor accelerates, decelerates, and may slip.")
    doc.add_paragraph("5.1 Determine mm/count and sign", style="Heading 2")
    add_steps(
        doc,
        [
            "Mark two belt positions 500-1000 mm apart; stop at the first position and reset the encoder.",
            "Move in the production direction to the second position and record the count or reported-position difference.",
            "Calculate mm_per_count = measured distance / count difference. Example: 1000 mm / 20000 counts = 0.05 mm/count.",
            "Repeat forward and reverse travel at least five times. If error changes with load, correct mechanical slip before software tuning.",
            "Verify sign: travel along +Y must increase C.Y. Reverse the sign in the encoder configuration or Reverse Value, never in several locations.",
        ],
        decimal_abs,
    )
    add_table(
        doc,
        ["Test", "Measured value", "Requirement"],
        [
            ["1000 mm travel", "________ mm", "Error below half of the pick tolerance"],
            ["Five repetitions", "Max-Min: ________", "No cumulative error growth"],
            ["Direction reversal", "Difference: ________", "Backlash is within budget"],
            ["Encoder loss", "Detection time: ________", "No new claims are issued"],
        ],
        [2400, 2300, 4660],
    )
    add_callout(doc, "ACCEPTANCE", "Cumulative camera-to-pick error is below the end-effector error budget, and workers receive no new object when encoder data is stale.", "success")

    section_heading(doc, "6. Camera and Image-Region Calibration")
    add_body(doc, "Fix resolution, focus, exposure, ROI, and camera position before collecting points. Any resize, crop, or warp change after calibration invalidates the matrix.")
    add_image(doc, CROPS / "camera_calibration.png", "Figure 7 - Object Detector image view, camera tools, and Calibration panel", 6.3)
    doc.add_paragraph("6.1 Correct perspective with a chessboard", style="Heading 2")
    add_steps(
        doc,
        [
            "Place a flat, undamaged chessboard on the belt plane and cover the camera work area.",
            "Click Find Chessboard. Select Edit chessboard for an existing setup or Find new chessboard for a new one.",
            "Enter the correct row/column count and square size; verify every detected corner.",
            "Correct misplaced corners with the adjustment tool, then enable Transform Image.",
            "Enable Crop Area and retain only the object path ROI; lock width, height, and exposure.",
        ],
        decimal_abs,
    )
    add_image(doc, RESOURCE / "press-find-chessboard.jpg", "Figure 8 - Find Chessboard: create or edit configuration", 4.6)
    add_image(doc, RESOURCE / "select-chessboard-size.jpg", "Figure 9 - Select the measured chessboard dimensions", 4.6)
    add_image(doc, RESOURCE / "transform.jpg", "Figure 10 - Enable Transform Image after all corners are correct", 4.7)
    add_image(doc, RESOURCE / "croped.jpg", "Figure 11 - Cropped ROI containing only the usable conveyor region", 4.7)
    add_callout(doc, "ACCEPTANCE", "Straight belt references remain straight throughout the ROI, perspective is negligible, and parts are not blurred at production speed.", "success")

    section_heading(doc, "7. Map Camera P to Conveyor C")
    add_body(doc, "P-to-C mapping converts a detection centre from pixels to millimetres. The two-point model is appropriate after perspective correction leaves only rotation, scale, and translation.")
    add_image(doc, CROPS / "mapping_detector.png", "Figure 12 - Calibration: P1/P2, real coordinates, offset, distance, and matrix calculation", 6.3)
    doc.add_paragraph("7.1 Two-point procedure", style="Heading 2")
    add_steps(
        doc,
        [
            "Enable Select Calibration Points, choose a clear belt reference T, and copy its image coordinates into P1.",
            "Enter the measured P1' coordinates in C. If the encoder was reset at T, use X=0 and Y=0.",
            "Move the conveyor exactly 80-100 mm using a measured reference or encoder travel.",
            "Select the same reference T again and copy its image coordinates into P2; enter P2' with unchanged X and encoder travel as Y.",
            "Click Calculate Mapping Matrix, assign a stable name, and use Test Calibration Point on points excluded from the fit.",
        ],
        decimal_abs,
    )
    add_image(doc, RESOURCE / "select-calib-point-tool.jpg", "Figure 13 - Select the Calibration Point tool", 4.8)
    add_image(doc, RESOURCE / "click-P1.jpg", "Figure 14 - Select reference T for P1", 4.8)
    add_image(doc, RESOURCE / "move-conveyor-100.jpg", "Figure 15 - Move the belt through a measured 100 mm travel", 4.8)
    add_image(doc, RESOURCE / "click-P2.jpg", "Figure 16 - Select the same reference T for P2", 4.8)
    add_callout(doc, "UPGRADE PATH", "If ROI-edge error is worse than centre error, use Cloud Point Mapping across the full ROI. Do not hide calibration error by increasing Distance Threshold.", "warning")

    section_heading(doc, "8. Map Conveyor C to Each Robot Ri")
    add_body(doc, "Every robot requires a separate matrix because position, mounting angle, and origin differ. Store matrices in the tracking group, for example #0.ConveyorToRobot0 and #0.ConveyorToRobot1.")
    add_image(doc, CROPS / "point_tool.png", "Figure 17 - Point Tool: Tracking Manager, velocity vector, and source/destination matrix", 6.3)
    add_steps(
        doc,
        [
            "Choose two widely separated belt references away from the edge of the robot workspace.",
            "At each reference, record C coordinates as Source; jog the robot to the same reference and record Ri as Destination.",
            "Click Calculate/Add Matrix and save it as the matching #0.ConveyorToRobotN.",
            "Validate at least three points excluded from fitting, including two pick-zone corners and one centre point.",
            "Teach SafeZ, PickZ, PlaceX/Y/Z, AngleOffset, and angle sign independently for each robot.",
            "Transform belt velocity from C to Ri. The SYNC vector is mm/s in robot axes, never counts/s or pixels/s.",
        ],
        decimal_abs,
    )
    add_image(doc, RESOURCE / "tracking vector.jpg", "Figure 18 - Encoder and velocity vector in Tracking Manager", 4.7)
    add_table(
        doc,
        ["Robot i parameter", "Taught value", "Verification"],
        [
            ["ConveyorToRobotN", "________________", "Maximum error ______ mm"],
            ["SafeZ / PickZ", "______ / ______ mm", "No collision / reliable pickup"],
            ["Place XYZ", "________________", "Correct bin and recipe"],
            ["AngleOffset", "______ deg", "Correct at 0/45/90 deg"],
            ["BeltVector", "(____, ____, ____) mm/s", "Robot follows the correct direction"],
        ],
        [2500, 3300, 3560],
    )

    section_heading(doc, "9. Detector and Tracking Configuration")
    add_image(doc, CROPS / "detector_thresholds.png", "Figure 19 - IoU, distance, type, dimensions, and detector limits", 6.3)
    doc.add_paragraph("9.1 Select a detector", style="Heading 2")
    add_table(
        doc,
        ["Detector", "Use when", "Parameters to fix"],
        [
            ["Find Blobs", "Background and objects have stable colour contrast", "Colour filter, min/max width/length"],
            ["Find Circles", "Parts are circular with clear edges", "Radius and centre distance"],
            ["External Script", "Several classes or complex shapes require AI/YOLO", "Model, class-to-type map, coordinateSpace"],
        ],
        [1800, 3500, 4060],
    )
    doc.add_paragraph("9.2 Tune association", style="Heading 2")
    add_bullets(
        doc,
        [
            "DistanceThreshold must exceed v_belt x frame_period + 2 x detection_error but remain below minimum part separation.",
            "IoUThreshold must tolerate inter-frame movement without allowing nearby parts to exchange UIDs.",
            "One detection associates with at most one track per cycle. Monitor ID, Type, X, Y, Angle, and Is Picked.",
            "Tracking rejects new claims when detections or encoder data exceed the stale limit (2 seconds by default).",
        ],
        bullet_num,
    )
    add_image(doc, CROPS / "tracking_table.png", "Figure 20 - #Objects table for UID, type, pose, angle, and picked state", 6.3)
    doc.add_paragraph("9.3 External detector", style="Heading 2")
    add_image(doc, RESOURCE / "select-external-algorithm.jpg", "Figure 21 - Select External Script as the detecting algorithm", 4.8)
    add_image(doc, RESOURCE / "yolov-detect.jpg", "Figure 22 - YOLO detection with bounding box and angle", 4.8)
    add_code(
        doc,
        '{\n  "type": "objects",\n  "coordinateSpace": "image",\n'
        '  "listName": "#Objects",\n  "list": [\n'
        '    {"type": 0, "x": 412.5, "y": 238.0, "z": 0,\n'
        '     "w": 35, "h": 62, "angle": 17, "isPicked": false}\n'
        '  ]\n}',
    )
    add_callout(doc, "DATA CONTRACT", "The detector never assigns UIDs. Use coordinateSpace=image for pixel x/y; use conveyor only when the detector returns calibrated C coordinates in millimetres.", "info")

    section_heading(doc, "10. Multi-Robot G-Script Configuration")
    add_body(doc, "Use exactly one vision loop for tracking0 and one worker loop per robot. Never run multiple vision threads that publish into the same tracking ID.")
    add_table(
        doc,
        ["Thread", "Script", "Responsibility"],
        [
            ["Vision", "00-vision-tracking.gcode", "Continuously capture, detect, and commit correlated frames"],
            ["Robot 0", "10-robot0-type0.gcode", "Claim type 0 in robot0 zone, pick, and place"],
            ["Robot 1", "11-robot1-type1.gcode", "Claim type 1 in robot1 zone, pick, and place"],
        ],
        [1600, 3000, 4760],
    )
    doc.add_paragraph("10.1 Vision loop", style="Heading 2")
    add_image(doc, CROPS / "vision_script.png", "Figure 23 - Load multi-robot-sorting and open the vision loop in the G-Script editor", 6.3)
    add_code(
        doc,
        "; One and only one vision loop for tracking0.\n"
        "N25 LABEL VISION_LOOP\n"
        "N30 M98 PcaptureAndDetect(0)\n"
        "N50 M98 Pdelay(20)\n"
        "N55 JUMP VISION_LOOP",
    )
    add_callout(doc, "CURRENT EXAMPLE", "The current vision example uses PcaptureAndDetect, which waits for FrameReady. Do not add a fixed detector delay; use the primitive timeout and measured telemetry.", "warning")
    doc.add_paragraph("10.2 Worker loop and atomic claim", style="Heading 2")
    add_image(doc, CROPS / "worker_script.png", "Figure 24 - robot0 worker: claim, Map, G01 SYNC, complete, and place", 6.3)
    add_code(
        doc,
        "M98 PclaimObject(0,#R0Target,robot0,-180,180,300,450,0,30000)\n\n"
        "IF #R0Target.Found == 1\n"
        "    #R0Pick = #0.ConveyorToRobot0.Map(#R0Target.X,#R0Target.Y)\n"
        "    G01 X[#R0Pick.X] Y[#R0Pick.Y] Z[#R0SafeZ] F1200 SYNC\n"
        "    G01 X[#R0Pick.X] Y[#R0Pick.Y] Z[#R0PickZ] F500 SYNC\n"
        "    M03\n"
        "    M98 Pdelay(60)\n"
        "    M98 PcompleteObject(0,#R0Target.UID,robot0)\n"
        "ENDIF",
    )
    add_table(
        doc,
        ["Primitive", "When to use", "Rule"],
        [
            ["claimObject", "Before a robot approaches a part", "Continue only when Found=1"],
            ["releaseObject", "Abandoning a part before pickup", "Use the matching UID and owner"],
            ["completeObject", "After the end effector secures the part", "Never complete before pickup confirmation"],
        ],
        [2000, 3200, 4160],
    )
    add_callout(doc, "OWNERSHIP", "On ReleaseRejected or CompleteRejected, stop the worker in a controlled manner. Never continue with an old pose when ownership is uncertain.", "danger")

    section_heading(doc, "11. Operating Sequence")
    doc.add_paragraph("11.1 Start of shift", style="Heading 2")
    add_steps(
        doc,
        [
            "Inspect robot workspaces, E-stop, guards, air/vacuum, and obstructions while the conveyor is stopped.",
            "Open the software, load the approved project/recipe, and confirm G-Script paths.",
            "Connect robots, conveyor, encoder, and camera. Confirm that every COM port and IP address maps to the intended device.",
            "Home each robot at low speed; verify SafeZ and a safe end-effector state.",
            "Reset the encoder at the reference and verify sign and stable velocity at low belt speed.",
            "Run the vision thread only; confirm stable UIDs through the ROI and live updates in #Objects.",
            "Dry-run robot0 with the end effector disabled or PickZ raised. Perform a real pick with one robot only after the dry run passes.",
            "Enable additional robots one at a time while monitoring claim owners and non-overlapping workspaces.",
        ],
        decimal_abs,
    )
    add_callout(doc, "RUN CONDITIONS", "Camera/detector and encoder are fresh; mapping has passed validation; robots are homed; the vision loop is active; and no stale track or claim remains from a previous run.", "success")
    doc.add_paragraph("11.2 Production monitoring", style="Heading 2")
    add_table(
        doc,
        ["Observation", "Normal", "Stop condition"],
        [
            ["UID", "Stable throughout the ROI", "UID exchange or ghost track"],
            ["Encoder", "Continuous position and velocity", "Frozen, sign jumps, or stale"],
            ["Claim", "One owner per UID", "Two workers on one part or repeated lease expiry"],
            ["Pick", "Stable error", "Error grows with position or speed"],
            ["Cycle time", "Within the approved baseline", "Increase caused by inference, wait, or robot timeout"],
        ],
        [1800, 3300, 4260],
    )
    doc.add_paragraph("11.3 Normal stop", style="Heading 2")
    add_steps(
        doc,
        [
            "Stop feeding new parts and let claimed parts complete or release.",
            "Stop robot workers, then stop the vision loop.",
            "Stop the conveyor, move robots to approved safe poses, and disable end effectors.",
            "Save only approved project/configuration changes; never persist unreviewed test values.",
        ],
        decimal_abs,
    )

    section_heading(doc, "12. Fault Recovery and Troubleshooting")
    add_table(
        doc,
        ["Symptom", "Likely cause", "Action"],
        [
            ["No part can be claimed", "Stale detector/encoder or wrong zone/type", "Check freshness, C.X/C.Y, and typeFilter"],
            ["UID changes between frames", "Distance/IoU too strict or latency too high", "Measure motion per frame and retune thresholds"],
            ["Pick error grows with Y", "Incorrect mm/count or BeltVector", "Recalibrate encoder and SYNC vector"],
            ["Pick error at ROI edges", "Insufficient warp or P-to-C mapping", "Correct perspective or use Cloud Point Mapping"],
            ["Position correct, angle wrong", "AngleOffset, sign, or mirror", "Test 0/45/90 deg; correct sign before offset"],
            ["CompleteRejected", "Expired lease, wrong owner, or changed UID", "Stop the worker and discard the old target"],
            ["GigE camera not listed", "Missing vendor runtime, NIC, or subnet", "Install pylon/MVS and verify IP/firewall policy"],
            ["G-Script help missing", "GScript_Documentation.html absent", "Restore the file in the portable application directory"],
        ],
        [2100, 3500, 3760],
    )
    add_callout(doc, "CAMERA OR ENCODER LOSS", "Stop part feeding and robots through the cell state machine. Shared tracking blocks new claims when stale but does not replace cell-level controlled-stop logic.", "danger")
    doc.add_paragraph("Recover a worker terminated after claiming", style="Heading 2")
    add_steps(
        doc,
        [
            "Stop the conveyor and robot safely, then determine whether the part was physically picked.",
            "If not picked, wait for lease expiry or release with the matching owner/UID. Never delete a track while its worker still runs.",
            "If picked but not completed, handle the part through the approved recovery procedure and clear state under supervisor authority.",
            "Run vision only and verify a stable shared map before restarting any worker.",
        ],
        decimal_abs,
    )

    section_heading(doc, "13. Cell Acceptance")
    add_table(
        doc,
        ["Area", "Test", "Acceptance criterion", "Result"],
        [
            ["Encoder", "Five 1000 mm cycles", "Error within pick budget", "___"],
            ["P-to-C mapping", "Nine points across ROI", "Maximum/RMS error accepted", "___"],
            ["C-to-Ri mapping", "Three points per robot", "Within suction/grip radius", "___"],
            ["Tracking", "100 consecutive parts", "No out-of-policy UID exchange/ghost", "___"],
            ["Ownership", "Two workers compete for one part", "Exactly one Found=1", "___"],
            ["Lease", "Terminate worker after claim", "Part unlocks only after lease", "___"],
            ["Stale input", "Disconnect encoder/camera", "No new claim; cell stops", "___"],
            ["Throughput", "Run target speed", "Cycle time and reject rate accepted", "___"],
            ["Safety", "Test E-stop and guard", "Stops independently of PC/G-Script", "___"],
        ],
        [1400, 2600, 4060, 1300],
    )
    add_callout(doc, "PRODUCTION GATE", "Enter production only after every item passes and the acceptance record is approved. Collision avoidance, pickup sensors, recipe/bin logic, and the cell fault state machine require separate assessment.", "warning")
    doc.add_paragraph("Calibration record", style="Heading 2")
    add_table(
        doc,
        ["Parameter", "Value", "Date / performed by"],
        [
            ["Camera resolution / exposure / ROI", "____________________________", "________________"],
            ["mm_per_count / encoder sign", "____________________________", "________________"],
            ["Mapping P->C max/RMS", "____________________________", "________________"],
            ["ConveyorToRobot0 max error", "____________________________", "________________"],
            ["ConveyorToRobot1 max error", "____________________________", "________________"],
            ["DistanceThreshold / IoU", "____________________________", "________________"],
            ["Detector latency / frame period", "____________________________", "________________"],
            ["LeaseMs / stale timeout", "____________________________", "________________"],
        ],
        [3200, 3860, 2300],
    )

    section_heading(doc, "14. Parameter and Path Reference")
    add_table(
        doc,
        ["Asset", "Repository path"],
        [
            ["Design guide", "docs/multi-robot-conveyor-sorting.md"],
            ["Vision loop", "script-example/multi-robot-sorting/00-vision-tracking.gcode"],
            ["Robot0 worker", "script-example/multi-robot-sorting/10-robot0-type0.gcode"],
            ["Robot1 worker", "script-example/multi-robot-sorting/11-robot1-type1.gcode"],
            ["Test ownership", "tests/tracking_claim/"],
        ],
        [2700, 6660],
    )
    doc.add_paragraph("Claim result variables", style="Heading 2")
    add_code(
        doc,
        "#result.Found\n#result.UID\n#result.Type\n"
        "#result.X  #result.Y  #result.Z\n"
        "#result.W  #result.L  #result.A\n"
        "#result.ClaimOwner\n#result.ClaimExpiresAt",
    )
    add_callout(doc, "CURRENT BOUNDARY", "The platform provides shared tracking, atomic claims, leases, type/pose, and sample workers. A production cell must additionally validate multi-robot collision prevention, pickup quality confirmation, recipe/bin logic, OEE, and the cell-level fault/recovery state machine.", "info")

    for section in doc.sections:
        configure_section(section)

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    doc.save(OUTPUT)
    print(OUTPUT)


if __name__ == "__main__":
    build_document()
