//
//  ct26.h
//  L2UIUnpack
//

#ifndef ct26_h
#define ct26_h

#include <memory>

#include "Element.h"
#include "Schema.h"

namespace CT26 {
	struct AnchorType : public EnumAttribute {
		AnchorType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "TopLeft", "TopCenter",
			"TopRight", "CenterLeft", "CenterCenter", "CenterRight", "BottomLeft", "BottomCenter",
			"BottomRight"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct AnimType : public EnumAttribute {
		AnimType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "None", "None",
			"AlphaTransition", "PositionTransition"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct FrameSizeType : public EnumAttribute {
		FrameSizeType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"Big", "Small"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct DirectionType : public EnumAttribute {
		DirectionType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "Left",
			"Right", "Top", "Bottom", "Free"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct FontType : public EnumAttribute {
		FontType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"Normal", "SpecialDigitSmall", "SpecialDigitLarge", "SpecialDigitXLarge"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct FontLineType : public EnumAttribute {
		FontLineType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"empty", "none", "underline", "strike-through"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct TextAlignType : public EnumAttribute {
		TextAlignType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"undefined", "Left", "Center", "Right", "MacroIcon"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct TextVAlignType : public EnumAttribute {
		TextVAlignType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"undefined", "Top", "Middle", "Bottom"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct EditBoxType : public EnumAttribute {
		EditBoxType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"Default", "Chat", "Password", "Number", "None", "Date", "Time", "ID"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct AutoCompletionType : public EnumAttribute {
		AutoCompletionType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"NotUsed", "Normal", "PostBox"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct TextureCtrlType : public EnumAttribute {
		TextureCtrlType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"Stretch", "Normal", "Tile", "Draggable", "Control", "Mask"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct TextureLayer : public EnumAttribute {
		TextureLayer(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "Normal", "Background"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct AutoRotateType : public EnumAttribute {
		AutoRotateType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "Camera", "Pawn"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct EffectButtonType : public EnumAttribute {
		EffectButtonType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"Tutorial", "Quest", "Mail"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable);
		};
	};
	
	struct ProgressBarType : public EnumAttribute {
		ProgressBarType(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {"None", "RightLeft", "LeftRight", "TopBottom", "BottomTop"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct StrokeVolume : public EnumAttribute {
		StrokeVolume(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {
			if (value > 1)
				value = 1; /* FIXME */
		};
		static constexpr const char* nameTable[] {"thin", "thick"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct InputKey : public EnumAttribute {
		InputKey(int fdes, const char* name = "", bool hidden = false) : EnumAttribute(fdes, name, hidden) {};
		static constexpr const char* nameTable[] {
			"None",
			"LeftMouse",
			"RightMouse",
			"Cancel",
			"MiddleMouse",
			"Unknown05",
			"Unknown06",
			"Unknown07",
			"Backspace",
			"Tab",
			"Unknown0A",
			"Unknown0B",
			"Unknown0C",
			"Enter",
			"Unknown0E",
			"Unknown0F",
			"Shift",
			"Ctrl",
			"Alt",
			"Pause",
			"CapsLock",
			"Unknown15",
			"Unknown16",
			"Unknown17",
			"Unknown18",
			"Unknown19",
			"Unknown1A",
			"Escape",
			"Unknown1C",
			"Unknown1D",
			"Unknown1E",
			"Unknown1F",
			"Space",
			"PageUp",
			"PageDown",
			"End",
			"Home",
			"Left",
			"Up",
			"Right",
			"Down",
			"Select",
			"Print",
			"Execute",
			"PrintScrn",
			"Insert",
			"Delete",
			"Help",
			"0",
			"1",
			"2",
			"3",
			"4",
			"5",
			"6",
			"7",
			"8",
			"9",
			"Unknown3A",
			"Unknown3B",
			"Unknown3C",
			"Unknown3D",
			"Unknown3E",
			"Unknown3F",
			"Unknown40",
			"A",
			"B",
			"C",
			"D",
			"E",
			"F",
			"G",
			"H",
			"I",
			"J",
			"K",
			"L",
			"M",
			"N",
			"O",
			"P",
			"Q",
			"R",
			"S",
			"T",
			"U",
			"V",
			"W",
			"X",
			"Y",
			"Z",
			"Unknown5B",
			"Unknown5C",
			"Unknown5D",
			"Unknown5E",
			"Unknown5F",
			"NumPad0",
			"NumPad1",
			"NumPad2",
			"NumPad3",
			"NumPad4",
			"NumPad5",
			"NumPad6",
			"NumPad7",
			"NumPad8",
			"NumPad9",
			"GreyStar",
			"GreyPlus",
			"Separator",
			"GreyMinus",
			"NumPadPeriod",
			"GreySlash",
			"F1",
			"F2",
			"F3",
			"F4",
			"F5",
			"F6",
			"F7",
			"F8",
			"F9",
			"F10",
			"F11",
			"F12",
			"F13",
			"F14",
			"F15",
			"F16",
			"F17",
			"F18",
			"F19",
			"F20",
			"F21",
			"F22",
			"F23",
			"F24",
			"Unknown88",
			"Unknown89",
			"Unknown8A",
			"Unknown8B",
			"Unknown8C",
			"Unknown8D",
			"Unknown8E",
			"Unknown8F",
			"NumLock",
			"ScrollLock",
			"Unknown92",
			"Unknown93",
			"Unknown94",
			"Unknown95",
			"Unknown96",
			"Unknown97",
			"Unknown98",
			"Unknown99",
			"Unknown9A",
			"Unknown9B",
			"Unknown9C",
			"Unknown9D",
			"Unknown9E",
			"Unknown9F",
			"LShift",
			"RShift",
			"LControl",
			"RControl",
			"UnknownA4",
			"UnknownA5",
			"UnknownA6",
			"UnknownA7",
			"UnknownA8",
			"UnknownA9",
			"UnknownAA",
			"UnknownAB",
			"UnknownAC",
			"UnknownAD",
			"UnknownAE",
			"UnknownAF",
			"UnknownB0",
			"UnknownB1",
			"UnknownB2",
			"UnknownB3",
			"UnknownB4",
			"UnknownB5",
			"UnknownB6",
			"UnknownB7",
			"UnknownB8",
			"Unicode",
			"Semicolon",
			"Equals",
			"Comma",
			"Minus",
			"Period",
			"Slash",
			"Tilde",
			"UnknownC1",
			"UnknownC2",
			"UnknownC3",
			"UnknownC4",
			"UnknownC5",
			"UnknownC6",
			"UnknownC7",
			"Joy1",
			"Joy2",
			"Joy3",
			"Joy4",
			"Joy5",
			"Joy6",
			"Joy7",
			"Joy8",
			"Joy9",
			"Joy10",
			"Joy11",
			"Joy12",
			"Joy13",
			"Joy14",
			"Joy15",
			"Joy16",
			"UnknownD8",
			"UnknownD9",
			"UnknownDA",
			"LeftBracket",
			"Backslash",
			"RightBracket",
			"SingleQuote",
			"UnknownDF",
			"UnknownE0",
			"UnknownE1",
			"UnknownE2",
			"UnknownE3",
			"MouseX",
			"MouseY",
			"MouseZ",
			"MouseW",
			"JoyU",
			"JoyV",
			"JoySlider1",
			"JoySlider2",
			"MouseWheelUp",
			"MouseWheelDown",
			"Unknown10E",
			"UK_Unknown10F",
			"JoyX",
			"JoyY",
			"JoyZ",
			"JoyR",
			"UnknownF4",
			"UnknownF5",
			"Attn",
			"CrSel",
			"ExSel",
			"ErEof",
			"Play",
			"Zoom",
			"NoName",
			"PA1",
			"OEMClear",
		};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct Action : public EnumAttribute {
		Action(int fdes, const char* name = "", bool hidden = false, bool force = false) : EnumAttribute(fdes, name, hidden, force) {};
		static constexpr const char* nameTable[] {"None", "Press", "Hold", "Release", "Axis"};
		
		virtual const char* const* getNameTable() const override {
			return nameTable;
		};
		
		virtual size_t getNameTableSz() const override {
			return sizeof(nameTable) / sizeof(*nameTable);
		};
	};
	
	struct Drawer : public Element {
		Drawer(int fdes);
	};
	
	struct Iconable : public Element {
		Iconable(int fdes);
	};
	
	struct ResizeFrame : public Element {
		ResizeFrame(int fdes);
	};
	
	struct ShortcutItem : public Element {
		ShortcutItem(int fdes);
	};
	
	struct ShortcutSpecialItem : public Element {
		ShortcutSpecialItem(int fdes);
	};
	
	struct Shortcut : public Element {
		Shortcut(int fdes);
	};
	
	struct Tooltip : public Element {
		Tooltip(int fdes);
	};
	
	struct Anim : public Element {
		Anim(int fdes, std::unique_ptr<AnimType> type, const char* tag = "");
	};
	
	struct Frame : public Element {
		Frame(int fd, std::unique_ptr<FrameSizeType> size, std::unique_ptr<DirectionType> direction, std::unique_ptr<BoolAttribute> exitbutton);
	};
	
	struct AdditionalState : public Element {
		AdditionalState(int fd);
	};
	
	struct ShowHideAnim : public Element {
		ShowHideAnim(int fdes, std::unique_ptr<AnimType> showAnimType,
					 std::unique_ptr<AnimType> hideAnimType);
		
		struct ShowAnim : public Anim {
			ShowAnim(int fdes, std::unique_ptr<AnimType> type);
		};
		struct HideAnim : public Anim {
			HideAnim(int fdes, std::unique_ptr<AnimType> type);
		};
	};
	
	struct Color : public Element {
		Color(int fdes, const char* name = "Color");
	};
	
	struct Font : public Element {
		Font(int fdes);
	};
	
	struct AbsoluteSize : public Element {
		AbsoluteSize(int fdes);
	};
	
	struct RelativeSize : public Element {
		RelativeSize(int fdes);
	};
	
	struct Size : public Element {
		Size(int fdes);
	};
	
	struct ScrollBarOffset : public Element {
		ScrollBarOffset(int fdes);
	};
	
	struct Position : public Element {
		Position(int fdes, std::unique_ptr<BoolAttribute> anchored);
	};
	
	struct TabOrder : public Element {
		TabOrder(int fdes);
	};
	
	struct Window : public Element {
		Window(int fdes);
	};
	
	struct DefaultProperty : public Element {
		DefaultProperty(int fdes);
	};
	
	struct DefaultPosition : public Element {
		DefaultPosition(int fdes);
	};
	
	struct DefaultPositionItem : public Element {
		DefaultPositionItem(int fdes);
	};
	
	struct DefaultPositionItemSize : public Element {
		DefaultPositionItemSize(int fdes);
	};
	
	struct DefaultPositionItemPosition : public Element {
		DefaultPositionItemPosition(int fdes);
	};
	
	struct FontData : public Element {
		FontData(int fdes);
	};
	
	struct FontDefinition : public Element {
		FontDefinition(int fdes);
	};
	
	struct Style : public Element {
		Style(int fdes);
	};
	
	struct ChatChannelDefinition : public Element {
		ChatChannelDefinition(int fdes);
	};
	
	struct ChatChannel : public Element {
		ChatChannel(int fdes);
	};
	
	struct StatusIconCtrl : public Element {
		StatusIconCtrl(int fdes);
	};
	
	struct Button : public Element {
		Button(int fdes);
	};
	
	struct TextBox : public Element {
		TextBox(int fdes);
	};
	
	struct EditBox : public Element {
		EditBox(int fdes);
	};
	
	struct Texture : public Element {
		Texture(int fdes);
	};
	
	struct ChatWindow : public Element {
		ChatWindow(int fdes);
	};
	
	struct TextureCoords : public Element {
		TextureCoords(int fdes, const char* name = "TextureCoords");
	};
	
	struct Tab : public Element {
		Tab(int fdes);
	};
	
	struct TabButton : public Element {
		TabButton(int fdes);
	};
	
	struct ItemWindow : public Element {
		ItemWindow(int fdes);
	};
	
	struct Item : public Element {
		Item(int fdes, const char* name);
	};
	
	struct ButtonItem : public Element {
		ButtonItem(int fdes, const char* name = "ButtonItem");
	};
	
	struct ExpandItem : public Element {
		ExpandItem(int fdes);
	};
	
	struct CheckBox : public Element {
		CheckBox(int fdes);
	};
	
	struct ComboBox : public Element {
		ComboBox(int fdes);
	};
	
	struct ComboItem : public Element {
		ComboItem(int fdes);
	};
	
	struct Progress : public Element {
		Progress(int fdes);
	};
	
	struct MultiEdit : public Element {
		MultiEdit(int fdes);
	};
	
	struct ListCtrl : public Element {
		ListCtrl(int fdes);
	};
	
	struct ListColumn : public Element {
		ListColumn(int fdes);
	};
	
	struct ListBox : public Element {
		ListBox(int fdes);
	};
	
	struct StatusBar : public Element {
		StatusBar(int fdes);
	};
	
	struct GaugeText : public Element {
		GaugeText(int fdes, bool texture = true);
	};
	
	struct NameCtrl : public Element {
		NameCtrl(int fdes);
	};
	
	struct MinimapCtrl : public Element {
		MinimapCtrl(int fdes);
	};
	
	struct ShortcutItemWindow : public Element {
		ShortcutItemWindow(int fdes);
	};
	
	struct TreeCtrl : public Element {
		TreeCtrl(int fdes);
	};
	
	struct SliderCtrl : public Element {
		SliderCtrl(int fdes);
	};
	
	struct EffectButton : public Element {
		EffectButton(int fdes);
	};
	
	struct TextListBox : public Element {
		TextListBox(int fdes);
	};
	
	struct Radar : public Element {
		Radar(int fdes);
	};
	
	struct HtmlCtrl : public Element {
		HtmlCtrl(int fdes);
	};
	
	struct RadioButton : public Element {
		RadioButton(int fdes);
	};
	
	struct InvenWeight : public Element {
		InvenWeight(int fdes);
	};
	
	struct BarCtrl : public Element {
		BarCtrl(int fdes);
	};
	
	struct ScrollArea : public Element {
		ScrollArea(int fdes);
	};
	
	struct FishViewportWindow : public Element {
		FishViewportWindow(int fdes);
	};
	
	struct MultiSellItemInfo : public Element {
		MultiSellItemInfo(int fdes);
	};
	
	struct MultiSellNeededItem : public Element {
		MultiSellNeededItem(int fdes);
	};
	
	struct DrawPanel : public Element {
		DrawPanel(int fdes);
	};
	
	struct RadarMapCtrl : public Element {
		RadarMapCtrl(int fdes);
	};
	
	struct RadarMapCtrlObjectType : public Element {
		RadarMapCtrlObjectType(int fdes);
	};
	
	struct PropertyController : public Element {
		PropertyController(int fdes);
	};
	
	struct MoviePlayerCtrl : public Element {
		MoviePlayerCtrl(int fdes);
	};
	
	struct FlashCtrl : public Element {
		FlashCtrl(int fdes);
	};
	
	struct CharacterViewportWindow : public Element {
		CharacterViewportWindow(int fdes);
	};
	
	struct Shadow : public Element {
		Shadow(int fdes);
	};
	
	struct Stroke : public Element {
		Stroke(int fdes);
	};
	
	struct Constant : public Element {
		Constant(int fdes);
	};
	
	struct ConstantInt : public Element {
		ConstantInt(int fdes);
	};
	
	struct ConstantString : public Element {
		ConstantString(int fdes);
	};
	
	struct ConstantBool : public Element {
		ConstantBool(int fdes);
	};
	
	struct ConstantFloat : public Element {
		ConstantFloat(int fdes);
	};
	
	class Schema : public ::Schema {
	public:
		Schema() = delete;
		Schema(int fdes, const char* xdat_path = nullptr);
		
		static void readChildren(int fd, std::vector<std::unique_ptr<ElementBase>>& children);
	};
} /* namespace CT26 */

#endif /* ct26_h */
