//
//  ct26.cpp
//  L2UIUnpack
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

#include <fcntl.h>
#include <unistd.h>

#include "Attribute.h"
#include "ct26.h"

constexpr const char* CT26::AnchorType::nameTable[];
constexpr const char* CT26::AnimType::nameTable[];
constexpr const char* CT26::DirectionType::nameTable[];
constexpr const char* CT26::FrameSizeType::nameTable[];
constexpr const char* CT26::FontLineType::nameTable[];
constexpr const char* CT26::TextAlignType::nameTable[];
constexpr const char* CT26::TextVAlignType::nameTable[];
constexpr const char* CT26::FontType::nameTable[];
constexpr const char* CT26::EditBoxType::nameTable[];
constexpr const char* CT26::AutoCompletionType::nameTable[];
constexpr const char* CT26::TextureCtrlType::nameTable[];
constexpr const char* CT26::TextureLayer::nameTable[];
constexpr const char* CT26::AutoRotateType::nameTable[];
constexpr const char* CT26::EffectButtonType::nameTable[];
constexpr const char* CT26::ProgressBarType::nameTable[];
constexpr const char* CT26::StrokeVolume::nameTable[];
constexpr const char* CT26::InputKey::nameTable[];
constexpr const char* CT26::Action::nameTable[];

CT26::Schema::Schema(int fdes, const char* xdat_path) : ::Schema(Version::CT26, fdes, xdat_path) {
	list_children.emplace_back(new List<Shortcut>(fdes));
	list_children.emplace_back(new List<Window>(fdes));
	auto constant = IntAttribute(fdes);
//	if (constant.value) {
//		fprintf(stderr, "adding Constant %x\n", constant.value);
//		list_children.emplace_back(new List<Constant>(fdes));
//	}
	single_children.emplace_back(new DefaultPosition(fdes));
	list_children.emplace_back(new List<FontDefinition>(fdes));
	list_children.emplace_back(new List<Style>(fdes));
	single_children.emplace_back(new ChatChannelDefinition(fdes));
}

CT26::Anim::Anim(int fdes, std::unique_ptr<AnimType> type, const char* tag) : Element(fdes, tag) {
	children.emplace_back(std::move(type));
	children.emplace_back(new FloatAttribute(fdes, "direction"));
	children.emplace_back(new FloatAttribute(fdes, "seconds"));
}

CT26::Drawer::Drawer(int fdes) : Element(fdes, "Drawer") {
	auto direction = std::unique_ptr<DirectionType>(new DirectionType(fdes, "direction"));
	auto offsetX = std::unique_ptr<IntAttribute>(new IntAttribute(fdes, "offsetX"));
	auto offsetY = std::unique_ptr<IntAttribute>(new IntAttribute(fdes, "offsetY"));
	auto directionFixed = std::unique_ptr<BoolAttribute>(new BoolAttribute(fdes, "directionFixed"));
	auto ownerWindow = std::unique_ptr<StrAttribute>(new StrAttribute(fdes, "ownerWindow"));
	if (ownerWindow->value && strlen(reinterpret_cast<const char*>(ownerWindow->value.get())) > 0) {
		children.emplace_back(std::move(direction));
		children.emplace_back(std::move(offsetX));
		children.emplace_back(std::move(offsetY));
		children.emplace_back(std::move(directionFixed));
		children.emplace_back(std::move(ownerWindow));
	}
}

CT26::ResizeFrame::ResizeFrame(int fdes) : Element(fdes, "ResizeFrame") {
	children.emplace_back(new DirectionType(fdes, "direction"));
	auto x = FloatAttribute(fdes);
	auto y = FloatAttribute(fdes);
	auto width = FloatAttribute(fdes);
	auto height = FloatAttribute(fdes);
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(x.value)), "x"));
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(y.value)), "y"));
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(width.value)), "width"));
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(height.value)), "height"));
	children.emplace_back(new IntAttribute(fdes, "maxIncrease"));
}

CT26::ShortcutItem::ShortcutItem(int fdes) : Element(fdes, "ShortcutItem") {
	children.emplace_back(new InputKey(fdes, "key"));
	children.emplace_back(new InputKey(fdes, "subkey1"));
	children.emplace_back(new InputKey(fdes, "subkey2"));
	children.emplace_back(new StrAttribute(fdes, "command"));
	children.emplace_back(new Action(fdes, "action", false, true));
}

CT26::ShortcutSpecialItem::ShortcutSpecialItem(int fdes) : Element(fdes, "ShortcutSpecialItem") {
	children.emplace_back(new IntAttribute(fdes, "key"));
	children.emplace_back(new StrAttribute(fdes, "command"));
}

CT26::Shortcut::Shortcut(int fdes) : Element(fdes, "Shortcut") {
	children.emplace_back(new StrAttribute(fdes, "name"));
	children.emplace_back(new StrAttribute(fdes, "state"));
	children.emplace_back(new BoolAttribute(fdes, "modifiable"));
	children.emplace_back(new List<ShortcutItem>(fdes));
	children.emplace_back(new List<ShortcutSpecialItem>(fdes));
}

CT26::ShowHideAnim::ShowHideAnim(int fdes, std::unique_ptr<AnimType> showAnimType, std::unique_ptr<AnimType> hideAnimType) : Element(fdes, "ShowHideAnim") {
	children.emplace_back(new ShowAnim(fdes, std::move(showAnimType)));
	children.emplace_back(new HideAnim(fdes, std::move(hideAnimType)));
}

CT26::ShowHideAnim::ShowAnim::ShowAnim(int fdes, std::unique_ptr<AnimType> type) : CT26::Anim(fdes, std::move(type), "ShowAnim") {
}

CT26::ShowHideAnim::HideAnim::HideAnim(int fdes, std::unique_ptr<AnimType> type) : CT26::Anim(fdes, std::move(type), "HideAnim") {
}

CT26::Iconable::Iconable(int fdes) : Element(fdes, "Iconable") {
	children.emplace_back(new StrAttribute(fdes, "IconName"));
	children.emplace_back(new IntAttribute(fdes, "TooltipIdx"));
}

CT26::Frame::Frame(int fdes, std::unique_ptr<FrameSizeType> size, std::unique_ptr<DirectionType> direction, std::unique_ptr<BoolAttribute> exitbutton) : Element(fdes, "frame") {
	children.emplace_back(std::move(size));
	children.emplace_back(std::move(direction));
	children.emplace_back(std::move(exitbutton));
	children.emplace_back(new StrAttribute(fdes, "LeftTextureName"));
	children.emplace_back(new StrAttribute(fdes, "MidTextureName"));
	children.emplace_back(new StrAttribute(fdes, "RightTextureName"));
	children.emplace_back(new StrAttribute(fdes, "MinimizeBtnTextureNormal"));
	children.emplace_back(new StrAttribute(fdes, "MinimizeBtnTexturePushed"));
	children.emplace_back(new StrAttribute(fdes, "CloseBtnTextureNormal"));
	children.emplace_back(new StrAttribute(fdes, "CloseBtnTexturePushed"));
	children.emplace_back(new IntAttribute(fdes, "LeftBackTextureWidth"));
	children.emplace_back(new IntAttribute(fdes, "MidBackTextureWidth"));
}

CT26::AdditionalState::AdditionalState(int fdes) : Element(fdes, "AdditionalState") {
	children.emplace_back(new StrAttribute(fdes, "stateName"));
}

CT26::AbsoluteSize::AbsoluteSize(int fdes) : Element(fdes, "AbsoluteSize") {
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new IntAttribute(fdes, "height"));
}

CT26::Color::Color(int fdes, const char* name) : Element(fdes, name) {
	auto rgb = IntAttribute(fdes);
	auto r = std::unique_ptr<IntAttribute>(new IntAttribute(IntAttribute::IntValue(rgb.value >> 16 & 0xff), "R"));
	auto g = std::unique_ptr<IntAttribute>(new IntAttribute(IntAttribute::IntValue(rgb.value >> 8 & 0xff), "G"));
	auto b = std::unique_ptr<IntAttribute>(new IntAttribute(IntAttribute::IntValue(rgb.value & 0xff), "B"));
	if (!strncmp(name, "ColorModify", strlen("ColorModify")) && rgb.value == static_cast<int32_t>(0xffffffff))
		return;
	if (rgb.value == 0)
		return;
	children.emplace_back(std::move(r));
	children.emplace_back(std::move(g));
	children.emplace_back(std::move(b));
}

CT26::Font::Font(int fdes) : Element(fdes, "UseFont") {
	children.emplace_back(new StrAttribute(fdes, "styleName"));
	children.emplace_back(new StrAttribute(fdes, "fontName"));
	children.emplace_back(new Color(fdes));
	children.emplace_back(new FontLineType(fdes, "line"));
}

CT26::RelativeSize::RelativeSize(int fdes) : Element(fdes, "RelativeSize") {
	children.emplace_back(new StrAttribute(fdes, "windowRate", true));
	auto widthRate = FloatAttribute(fdes);
	auto heightRate = FloatAttribute(fdes);
	auto widthRateInt = std::unique_ptr<IntAttribute>(new IntAttribute(IntAttribute::IntValue(
		static_cast<int>(widthRate.value * 100)), "widthRate"));
	auto heightRateInt = std::unique_ptr<IntAttribute>(new IntAttribute(IntAttribute::IntValue(
		static_cast<int>(heightRate.value * 100)), "heightRate"));
	children.emplace_back(std::move(widthRateInt));
	children.emplace_back(std::move(heightRateInt));
	children.emplace_back(new IntAttribute(fdes, "offsetWidth"));
	children.emplace_back(new IntAttribute(fdes, "offsetHeight"));
}

CT26::DefaultProperty::DefaultProperty(int fdes) : Element(fdes, "DefaultProperty") {
	children.emplace_back(new StrAttribute(fdes, "name"));
	children.emplace_back(new StrAttribute(fdes, "extends"));
	children.emplace_back(new BoolAttribute(fdes, "alwaysOnTop"));
	children.emplace_back(new BoolAttribute(fdes, "alwaysOnBack"));
	children.emplace_back(new StrAttribute(fdes, "parentName", true));
	children.emplace_back(new TabOrder(fdes));
	auto anchored = std::unique_ptr<BoolAttribute>(new BoolAttribute(fdes, "anchored"));
	children.emplace_back(new BoolAttribute(fdes, "superChild"));
	children.emplace_back(new Size(fdes));
	auto position = BoolAttribute(fdes);
	if (position.value)
		children.emplace_back(new Position(fdes, std::move(anchored)));
	auto font = BoolAttribute(fdes);
	if (font.value)
		children.emplace_back(new Font(fdes));
	children.emplace_back(new BoolAttribute(fdes, "virtual"));
	children.emplace_back(new Tooltip(fdes));
	children.emplace_back(new ScrollBarOffset(fdes));
}

CT26::DefaultPosition::DefaultPosition(int fdes) : Element(fdes, "DefaultPosition") {
	children.emplace_back(new List<DefaultPositionItem>(fdes));
}

CT26::DefaultPositionItem::DefaultPositionItem(int fdes) : Element(fdes, "DefaultPositionItem") {
	children.emplace_back(new StrAttribute(fdes, "windowName"));
	children.emplace_back(new DefaultPositionItemPosition(fdes));
	children.emplace_back(new DefaultPositionItemSize(fdes));
}

CT26::DefaultPositionItemPosition::DefaultPositionItemPosition(int fdes) : Element(fdes, "Position") {
	children.emplace_back(new AnchorType(fdes, "relativePoint"));
	children.emplace_back(new IntAttribute(fdes, "offsetX"));
	children.emplace_back(new IntAttribute(fdes, "offsetY"));
	children.emplace_back(new BoolAttribute(fdes, "anchored"));
}

CT26::DefaultPositionItemSize::DefaultPositionItemSize(int fdes) : Element(fdes, "Size") {
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new IntAttribute(fdes, "height"));
}

CT26::Size::Size(int fdes) : Element(fdes, "Size") {
	auto size = BoolAttribute(fdes);
	if (size.value) {
		auto absolute = BoolAttribute(fdes);
		if (absolute.value)
			children.emplace_back(new AbsoluteSize(fdes));
		else
			children.emplace_back(new RelativeSize(fdes));
	}
}

CT26::TabOrder::TabOrder(int fdes) : Element(fdes, "TabOrder") {
	children.emplace_back(new StrAttribute(fdes, "preOrder"));
	children.emplace_back(new StrAttribute(fdes, "postOrder"));
}

CT26::Tooltip::Tooltip(int fdes) : Element(fdes, "Tooltip") {
	auto type_unused = IntAttribute(fdes);
	children.emplace_back(new StrAttribute(fdes, "type"));
	children.emplace_back(new IntAttribute(fdes, "text"));
	children.emplace_back(new IntAttribute(fdes, "appearanceTime"));
}

CT26::ScrollBarOffset::ScrollBarOffset(int fdes) : Element(fdes, "ScrollBarOffset") {
	children.emplace_back(new IntAttribute(fdes, "x"));
	children.emplace_back(new IntAttribute(fdes, "y"));
	children.emplace_back(new IntAttribute(fdes, "heightOffset"));
}

CT26::Position::Position(int fdes, std::unique_ptr<BoolAttribute> anchored) : Element(fdes, "Position") {
	children.emplace_back(new AnchorType(fdes, "anchorPoint"));
	children.emplace_back(new AnchorType(fdes, "relativePoint"));
	children.emplace_back(new StrAttribute(fdes, "relativeTo"));
	auto offsetX = FloatAttribute(fdes);
	auto offsetY = FloatAttribute(fdes);
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(offsetX.value)), "offsetX"));
	children.emplace_back(new IntAttribute(IntAttribute::IntValue(static_cast<int32_t>(offsetY.value)), "offsetY"));
	children.emplace_back(std::move(anchored));
}

CT26::FontData::FontData(int fdes) : Element(fdes, "FontData") {
	children.emplace_back(new StrAttribute(fdes, "name"));
	children.emplace_back(new StrAttribute(fdes, "fileName"));
	children.emplace_back(new StrAttribute(fdes, "location"));
	children.emplace_back(new IntAttribute(fdes, "size"));
	auto idx = new IntAttribute(fdes, "index");
	if (BoolAttribute(fdes).value)
		children.emplace_back(idx);
	auto shadow = BoolAttribute(fdes);
	if (shadow.value)
		children.emplace_back(new Shadow(fdes));
	else {
		auto unu0 = IntAttribute(fdes);
		auto unu1 = IntAttribute(fdes);
	}
	auto stroke = BoolAttribute(fdes);
	if (stroke.value)
		children.emplace_back(new Stroke(fdes));
	else
		auto unu0 = IntAttribute(fdes);
	children.emplace_back(new IntAttribute(fdes, "lineGap"));
	children.emplace_back(new IntAttribute(fdes, "underlineOffset"));
}

CT26::Shadow::Shadow(int fdes) : Element(fdes, "Shadow") {
	children.emplace_back(new IntAttribute(fdes, "offsetX"));
	children.emplace_back(new IntAttribute(fdes, "offsetY"));
}

CT26::Stroke::Stroke(int fdes) : Element(fdes, "Stroke") {
	children.emplace_back(new StrokeVolume(fdes, "volume"));
}

CT26::FontDefinition::FontDefinition(int fdes) : Element(fdes, "FontDefinition") {
	children.emplace_back(new StrAttribute(fdes, "defaultFontName"));
	children.emplace_back(new Color(fdes, "DefaultColor"));
	children.emplace_back(new List<FontData>(fdes));
}

CT26::Style::Style(int fdes) : Element(fdes, "Style") {
	children.emplace_back(new StrAttribute(fdes, "Name"));
	children.emplace_back(new StrAttribute(fdes, "FontName"));
	children.emplace_back(new StrAttribute(fdes, "Line"));
	children.emplace_back(new Color(fdes));
}

CT26::ChatChannelDefinition::ChatChannelDefinition(int fdes) : Element(fdes, "ChatChannelDefinition") {
	children.emplace_back(new List<ChatChannel>(fdes));
}

CT26::ChatChannel::ChatChannel(int fdes) : Element(fdes, "ChatChannel") {
	children.emplace_back(new IntAttribute(fdes, "Index"));
	children.emplace_back(new Color(fdes));
}

CT26::Window::Window(int fdes) : Element(fdes, "Window") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "parent"));
	children.emplace_back(new StrAttribute(fdes, "backTex"));
	children.emplace_back(new StrAttribute(fdes, "script"));
	children.emplace_back(new StrAttribute(fdes, "state"));
	children.emplace_back(new BoolAttribute(fdes, "frame"));
	children.emplace_back(new BoolAttribute(fdes, "iconable"));
	children.emplace_back(new BoolAttribute(fdes, "stuckable"));
	children.emplace_back(new BoolAttribute(fdes, "hidden"));
	children.emplace_back(new BoolAttribute(fdes, "alwaysFullAlpha"));
	children.emplace_back(new BoolAttribute(fdes, "savePosition"));
	children.emplace_back(new BoolAttribute(fdes, "saveSize"));
	children.emplace_back(new IntAttribute(fdes, "title"));
	children.emplace_back(new BoolAttribute(fdes, "resizeframe"));
	auto frameSize = std::unique_ptr<FrameSizeType>(new FrameSizeType(fdes, "size"));
	auto frameDirection = std::unique_ptr<DirectionType>(new DirectionType(fdes, "direction"));
	auto frameExitbutton = std::unique_ptr<BoolAttribute>(new BoolAttribute(fdes, "exitbutton"));
	children.emplace_back(new BoolAttribute(fdes, "draggable"));
	children.emplace_back(new ResizeFrame(fdes));
	children.emplace_back(new Drawer(fdes));
	auto showAnimType = std::unique_ptr<AnimType>(new AnimType(fdes, "type"));
	auto hideAnimType = std::unique_ptr<AnimType>(new AnimType(fdes, "type"));
	children.emplace_back(new ShowHideAnim(fdes, std::move(showAnimType), std::move(hideAnimType)));
	children.emplace_back(new Iconable(fdes));
	children.emplace_back(new BoolAttribute(fdes, "hookKeyInput"));
	children.emplace_back(new StrAttribute(fdes, "WorkingConfiguration"));
	children.emplace_back(new Frame(fdes, std::move(frameSize), std::move(frameDirection), std::move(frameExitbutton)));
	children.emplace_back(new List<AdditionalState, CompactIntAttribute>(fdes));
	children.emplace_back(new BoolAttribute(fdes, "UseParentClipRect"));
	CT26::Schema::readChildren(fdes, children);
}

void CT26::Schema::readChildren(int fdes, std::vector<std::unique_ptr<ElementBase>>& children) {
	auto nchildren = std::unique_ptr<IntAttribute>(new IntAttribute(fdes));

	for (int32_t i = 0; i < nchildren->value; i++) {
		auto name = std::unique_ptr<StrAttribute>(new StrAttribute(fdes));
		auto name_str = reinterpret_cast<const char*>(name->value.get());
	
		ElementBase* child = nullptr;
		if (!strncmp(name_str, "Window", name->len))
			child = new Window(fdes);
		else if (!strncmp(name_str, "Button", name->len))
			child = new Button(fdes);
		else if (!strncmp(name_str, "TextBox", name->len))
			child = new TextBox(fdes);
		else if (!strncmp(name_str, "EditBox", name->len))
			child = new EditBox(fdes);
		else if (!strncmp(name_str, "Texture", name->len))
			child = new Texture(fdes);
		else if (!strncmp(name_str, "ChatWindow", name->len))
			child = new ChatWindow(fdes);
		else if (!strncmp(name_str, "Tab", name->len))
			child = new Tab(fdes);
		else if (!strncmp(name_str, "ItemWindow", name->len))
			child = new ItemWindow(fdes);
		else if (!strncmp(name_str, "CheckBox", name->len))
			child = new CheckBox(fdes);
		else if (!strncmp(name_str, "ComboBox", name->len))
			child = new ComboBox(fdes);
		else if (!strncmp(name_str, "Progress", name->len))
			child = new Progress(fdes);
		else if (!strncmp(name_str, "MultiEdit", name->len))
			child = new MultiEdit(fdes);
		else if (!strncmp(name_str, "ListCtrl", name->len))
			child = new ListCtrl(fdes);
		else if (!strncmp(name_str, "ListBox", name->len))
			child = new ListBox(fdes);
		else if (!strncmp(name_str, "StatusBar", name->len))
			child = new StatusBar(fdes);
		else if (!strncmp(name_str, "NameCtrl", name->len))
			child = new NameCtrl(fdes);
		else if (!strncmp(name_str, "MinimapCtrl", name->len))
			child = new MinimapCtrl(fdes);
		else if (!strncmp(name_str, "ShortcutItemWindow", name->len))
			child = new ShortcutItemWindow(fdes);
		else if (!strncmp(name_str, "TreeCtrl", name->len))
			child = new TreeCtrl(fdes);
		else if (!strncmp(name_str, "SliderCtrl", name->len))
			child = new SliderCtrl(fdes);
		else if (!strncmp(name_str, "EffectButton", name->len))
			child = new EffectButton(fdes);
		else if (!strncmp(name_str, "TextListBox", name->len))
			child = new TextListBox(fdes);
		else if (!strncmp(name_str, "Radar", name->len))
			child = new Radar(fdes);
		else if (!strncmp(name_str, "HtmlCtrl", name->len))
			child = new HtmlCtrl(fdes);
		else if (!strncmp(name_str, "RadioButton", name->len))
			child = new RadioButton(fdes);
		else if (!strncmp(name_str, "InvenWeight", name->len))
			child = new InvenWeight(fdes);
		else if (!strncmp(name_str, "StatusIconCtrl", name->len))
			child = new StatusIconCtrl(fdes);
		else if (!strncmp(name_str, "BarCtrl", name->len))
			child = new BarCtrl(fdes);
		else if (!strncmp(name_str, "ScrollArea", name->len))
			child = new ScrollArea(fdes);
		else if (!strncmp(name_str, "FishViewportWindow", name->len))
			child = new FishViewportWindow(fdes);
		else if (!strncmp(name_str, "MultiSellItemInfo", name->len))
			child = new MultiSellItemInfo(fdes);
		else if (!strncmp(name_str, "MultiSellNeededItem", name->len))
			child = new MultiSellNeededItem(fdes);
		else if (!strncmp(name_str, "DrawPanel", name->len))
			child = new DrawPanel(fdes);
		else if (!strncmp(name_str, "RadarMapCtrl", name->len))
			child = new RadarMapCtrl(fdes);
		else if (!strncmp(name_str, "PropertyController", name->len))
			child = new PropertyController(fdes);
		else if (!strncmp(name_str, "MoviePlayerCtrl", name->len))
			child = new MoviePlayerCtrl(fdes);
		else if (!strncmp(name_str, "FlashCtrl", name->len))
			child = new FlashCtrl(fdes);
		else if (!strncmp(name_str, "CharacterViewportWindow", name->len))
			child = new CharacterViewportWindow(fdes);
		/* Not in release Interface.xdat */
//		else if (!strncmp(name_str, "SceneCameraCtrl", name->len))
//			child = new SceneCameraCtrl(fdes);
//		else if (!strncmp(name_str, "SceneNpcCtrl", name->len))
//			child = new SceneNpcCtrl(fdes);
//		else if (!strncmp(name_str, "ScenePcCtrl", name->len))
//			child = new ScenePcCtrl(fdes);
//		else if (!strncmp(name_str, "SceneMusicCtrl", name->len))
//			child = new SceneMusicCtrl(fdes);
//		else if (!strncmp(name_str, "SceneScreenCtrl", name->len))
//			child = new SceneScreenCtrl(fdes);
		else
			throw std::runtime_error("Unexpected child type " + std::string(name_str));
		
		children.emplace_back(std::unique_ptr<ElementBase>(child));
	}
}

CT26::StatusIconCtrl::StatusIconCtrl(int fdes) : Element(fdes, "StatusIconCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new BoolAttribute(fdes, "NoClip"));
	children.emplace_back(new BoolAttribute(fdes, "NoTooltip"));
}

CT26::Button::Button(int fdes) : Element(fdes, "Button") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "normalTex"));
	children.emplace_back(new StrAttribute(fdes, "pushedTex"));
	children.emplace_back(new StrAttribute(fdes, "highlightTex"));
	children.emplace_back(new StrAttribute(fdes, "dropTex"));
	children.emplace_back(new IntAttribute(fdes, "buttonName"));
	children.emplace_back(new StrAttribute(fdes, "buttonNameText"));
	children.emplace_back(new BoolAttribute(fdes, "noHighlight"));
	children.emplace_back(new BoolAttribute(fdes, "defaultSoundOn"));
	children.emplace_back(new IntAttribute(fdes, "DisableTime"));
}

CT26::TextBox::TextBox(int fdes) : Element(fdes, "TextBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "text"));
	children.emplace_back(new TextAlignType(fdes, "align"));
	children.emplace_back(new TextVAlignType(fdes, "valign"));
	children.emplace_back(new FontType(fdes, "specialFontType"));
	children.emplace_back(new StrAttribute(fdes, "backTex"));
	children.emplace_back(new IntAttribute(fdes, "sysstring"));
	children.emplace_back(new IntAttribute(fdes, "systemMsg"));
	children.emplace_back(new Color(fdes, "TextColor"));
	children.emplace_back(new BoolAttribute(fdes, "emoticon"));
	children.emplace_back(new BoolAttribute(fdes, "autosize"));
}

CT26::EditBox::EditBox(int fdes) : Element(fdes, "EditBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new EditBoxType(fdes, "editBoxType"));
	children.emplace_back(new IntAttribute(fdes, "maxLength"));
	children.emplace_back(new BoolAttribute(fdes, "bShowCursor"));
	children.emplace_back(new BoolAttribute(fdes, "ChatMarkOn"));
	children.emplace_back(new IntAttribute(fdes, "OffsetX"));
	children.emplace_back(new BoolAttribute(fdes, "bCandidateBoxShowUpPos"));
	children.emplace_back(new AutoCompletionType(fdes, "AutoCompletionType"));
}

CT26::Texture::Texture(int fdes) : Element(fdes, "Texture") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "file"));
	children.emplace_back(new StrAttribute(fdes, "AlphaMask"));
	children.emplace_back(new TextureCtrlType(fdes, "type"));
	children.emplace_back(new TextureLayer(fdes, "layer"));
	children.emplace_back(new TextureCoords(fdes));
	children.emplace_back(new IntAttribute(fdes, "alpha"));
	children.emplace_back(new BoolAttribute(fdes, "isAnimTex"));
	children.emplace_back(new StrAttribute(fdes, "AutoRotate"));
	children.emplace_back(new FloatAttribute(fdes, "MaskLayer"));
	children.emplace_back(new Color(fdes, "ColorModify"));
}

CT26::TextureCoords::TextureCoords(int fdes, const char* name) : Element(fdes, name) {
	children.emplace_back(new FloatAttribute(fdes, "u"));
	children.emplace_back(new FloatAttribute(fdes, "v"));
	children.emplace_back(new FloatAttribute(fdes, "usize", false, true));
	children.emplace_back(new FloatAttribute(fdes, "vsize", false, true));
}

CT26::ChatWindow::ChatWindow(int fdes) : Element(fdes, "ChatWindow") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "lineGap"));
	children.emplace_back(new IntAttribute(fdes, "NextLineOffsetX"));
}

CT26::Tab::Tab(int fdes) : Element(fdes, "Tab") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new List<TabButton>(fdes));
}

CT26::TabButton::TabButton(int fdes) : Element(fdes, "TabButton") {
	children.emplace_back(new IntAttribute(fdes, "buttonName"));
	children.emplace_back(new StrAttribute(fdes, "buttonNameText"));
	children.emplace_back(new StrAttribute(fdes, "target"));
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new IntAttribute(fdes, "height"));
	children.emplace_back(new StrAttribute(fdes, "normalTex"));
	children.emplace_back(new StrAttribute(fdes, "pushedTex"));
	children.emplace_back(new BoolAttribute(fdes, "movable"));
	children.emplace_back(new IntAttribute(fdes, "gap"));
	children.emplace_back(new IntAttribute(fdes, "tooltip"));
	children.emplace_back(new BoolAttribute(fdes, "noHighlight"));
}

CT26::ItemWindow::ItemWindow(int fdes) : Element(fdes, "ItemWindow") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "ItemWndType"));
	children.emplace_back(new IntAttribute(fdes, "col", false, true));
	children.emplace_back(new IntAttribute(fdes, "row", false, true));
	children.emplace_back(new IntAttribute(fdes, "maxItem"));
	children.emplace_back(new IntAttribute(fdes, "itemWidth"));
	children.emplace_back(new IntAttribute(fdes, "itemHeight"));
	children.emplace_back(new IntAttribute(fdes, "gapX"));
	children.emplace_back(new IntAttribute(fdes, "gapY"));
	children.emplace_back(new IntAttribute(fdes, "OffsetX"));
	children.emplace_back(new IntAttribute(fdes, "OffsetY"));
	children.emplace_back(new Item(fdes, "BackgroundItem"));
	children.emplace_back(new Item(fdes, "SelectedItem"));
	children.emplace_back(new Item(fdes, "UnselectedItem"));
	children.emplace_back(new Item(fdes, "BlankItem"));
	children.emplace_back(new BoolAttribute(fdes, "NoSelectItem"));
	children.emplace_back(new BoolAttribute(fdes, "NoItemDrag"));
	children.emplace_back(new BoolAttribute(fdes, "ButtonClick"));
	children.emplace_back(new BoolAttribute(fdes, "UseCoolTime"));
	children.emplace_back(new BoolAttribute(fdes, "noScroll"));
	children.emplace_back(new BoolAttribute(fdes, "ShowIconFrame"));
	children.emplace_back(new ButtonItem(fdes));
	children.emplace_back(new IntAttribute(fdes, "", true)); /* buttonTypePrevButtonPosX */
	children.emplace_back(new IntAttribute(fdes, "", true)); /* buttonTypePrevButtonPosY */
	children.emplace_back(new IntAttribute(fdes, "", true)); /* buttonTypeNextButtonPosX */
	children.emplace_back(new IntAttribute(fdes, "", true)); /* buttonTypeNextButtonPosY */
	children.emplace_back(new List<ExpandItem>(fdes));
}

CT26::Item::Item(int fdes, const char* name) : Element(fdes, name) {
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new IntAttribute(fdes, "height"));
	children.emplace_back(new StrAttribute(fdes, "texture"));
}

CT26::ButtonItem::ButtonItem(int fdes, const char* name) : Element(fdes, name) {
	children.emplace_back(new StrAttribute(fdes, "OutLineUp"));
	children.emplace_back(new StrAttribute(fdes, "OutLineDown"));
}

CT26::ExpandItem::ExpandItem(int fdes) : Element(fdes, "ExpandItem") {
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new IntAttribute(fdes, "height"));
	children.emplace_back(new IntAttribute(fdes, "num"));
	children.emplace_back(new StrAttribute(fdes, "texture"));
}

CT26::CheckBox::CheckBox(int fdes) : Element(fdes, "CheckBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "string"));
	children.emplace_back(new StrAttribute(fdes, "TitleText"));
	children.emplace_back(new BoolAttribute(fdes, "checked"));
	children.emplace_back(new BoolAttribute(fdes, "leftAlign"));
	children.emplace_back(new IntAttribute(fdes, "maxWidth"));
	children.emplace_back(new StrAttribute(fdes, "CheckTexture"));
	children.emplace_back(new StrAttribute(fdes, "UnCheckTexture"));
	children.emplace_back(new StrAttribute(fdes, "DisableTexture"));
	children.emplace_back(new StrAttribute(fdes, "DisableCheckTexture"));
}

CT26::ComboBox::ComboBox(int fdes) : Element(fdes, "ComboBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new List<ComboItem>(fdes));
}

CT26::ComboItem::ComboItem(int fdes) : Element(fdes, "ComboItem") {
	children.emplace_back(new IntAttribute(fdes, "sysstring"));
	children.emplace_back(new IntAttribute(fdes, "systemMsg"));
	children.emplace_back(new StrAttribute(fdes, "text"));
	children.emplace_back(new IntAttribute(fdes, "reserved"));
}

CT26::Progress::Progress(int fdes) : Element(fdes, "Progress") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "Type"));
	children.emplace_back(new StrAttribute(fdes, "backLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "backTexture"));
	children.emplace_back(new StrAttribute(fdes, "backRightTexture"));
	children.emplace_back(new StrAttribute(fdes, "barLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "barTexture"));
	children.emplace_back(new StrAttribute(fdes, "barRightTexture"));
	children.emplace_back(new IntAttribute(fdes, "gap"));
	children.emplace_back(new IntAttribute(fdes, "USize"));
	children.emplace_back(new IntAttribute(fdes, "VSize"));
}

CT26::MultiEdit::MultiEdit(int fdes) : Element(fdes, "MultiEdit") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "maxRow"));
	children.emplace_back(new IntAttribute(fdes, "showRow"));
}

CT26::ListCtrl::ListCtrl(int fdes) : Element(fdes, "ListCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "maxRow"));
	children.emplace_back(new IntAttribute(fdes, "showRow"));
	children.emplace_back(new BoolAttribute(fdes, "useScroll"));
	children.emplace_back(new IntAttribute(fdes, "contentsHeight"));
	children.emplace_back(new IntAttribute(fdes, "headerHeight"));
	children.emplace_back(new List<ListColumn>(fdes));
}

CT26::ListColumn::ListColumn(int fdes) : Element(fdes, "ListColumn") {
	children.emplace_back(new IntAttribute(fdes, "string"));
	children.emplace_back(new IntAttribute(fdes, "width"));
	children.emplace_back(new BoolAttribute(fdes, "bAscend"));
	children.emplace_back(new BoolAttribute(fdes, "bClickEnable"));
	children.emplace_back(new BoolAttribute(fdes, "bNumber"));
}

CT26::ListBox::ListBox(int fdes) : Element(fdes, "ListBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "maxRow"));
	children.emplace_back(new IntAttribute(fdes, "showRow"));
	children.emplace_back(new BoolAttribute(fdes, "showLastLine"));
}

CT26::StatusBar::StatusBar(int fdes) : Element(fdes, "StatusBar") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "Title"));
	children.emplace_back(new IntAttribute(fdes, "TextureWidth"));
	children.emplace_back(new IntAttribute(fdes, "TextureHeight"));
	children.emplace_back(new StrAttribute(fdes, "ForeTexture"));
	children.emplace_back(new StrAttribute(fdes, "ForeLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "ForeRightTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackRightTexture"));
	children.emplace_back(new StrAttribute(fdes, "RegenLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "RegenTexture"));
	children.emplace_back(new StrAttribute(fdes, "RegenRightTexture"));
	children.emplace_back(new StrAttribute(fdes, "WarnTexture"));
	children.emplace_back(new StrAttribute(fdes, "WarnLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "WarnRightTexture"));
	children.emplace_back(new GaugeText(fdes));
}

CT26::GaugeText::GaugeText(int fdes, bool texture) : Element(fdes, "GaugeText") {
	if (texture)
		children.emplace_back(new StrAttribute(fdes, "Texture"));
	children.emplace_back(new IntAttribute(fdes, "FontWidth"));
	children.emplace_back(new IntAttribute(fdes, "FontHeight"));
}

CT26::NameCtrl::NameCtrl(int fdes) : Element(fdes, "NameCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
}

CT26::MinimapCtrl::MinimapCtrl(int fdes) : Element(fdes, "MinimapCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new BoolAttribute(fdes, "showtime"));
	children.emplace_back(new BoolAttribute(fdes, "showtown"));
	children.emplace_back(new BoolAttribute(fdes, "showgrid"));
	children.emplace_back(new BoolAttribute(fdes, "showmylocmark"));
	children.emplace_back(new BoolAttribute(fdes, "showmyloctext"));
	children.emplace_back(new BoolAttribute(fdes, "showssqtext"));
}

CT26::ShortcutItemWindow::ShortcutItemWindow(int fdes) : Element(fdes, "ShortcutItemWindow") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new BoolAttribute(fdes, "alwaysShowOutline"));
	children.emplace_back(new BoolAttribute(fdes, "useReservedShortcut"));
}

CT26::TreeCtrl::TreeCtrl(int fdes) : Element(fdes, "TreeCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new BoolAttribute(fdes, "SaveExpandedNode"));
	children.emplace_back(new BoolAttribute(fdes, "MultiExpand"));
}

CT26::SliderCtrl::SliderCtrl(int fdes) : Element(fdes, "SliderCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "iNumOfTick"));
	children.emplace_back(new IntAttribute(fdes, "iCurrTick"));
	children.emplace_back(new IntAttribute(fdes, "iThumbBtnWidth"));
	children.emplace_back(new IntAttribute(fdes, "iThumbBtnHeight"));
	children.emplace_back(new StrAttribute(fdes, "strBackTexture"));
	children.emplace_back(new StrAttribute(fdes, "strDisableBackTexture"));
	children.emplace_back(new StrAttribute(fdes, "strThumbBtnNormalTexture"));
	children.emplace_back(new StrAttribute(fdes, "strThumbBtnDownTexture"));
	children.emplace_back(new IntAttribute(fdes, "iPushBtnWidth"));
	children.emplace_back(new IntAttribute(fdes, "iPushBtnHeight"));
	children.emplace_back(new IntAttribute(fdes, "iPushBtnAutoHitTime"));
	children.emplace_back(new StrAttribute(fdes, "strDecreaseBtnNormalTexture"));
	children.emplace_back(new StrAttribute(fdes, "strDecreaseBtnDownTexture"));
	children.emplace_back(new StrAttribute(fdes, "strIncreaseBtnNormalTexture"));
	children.emplace_back(new StrAttribute(fdes, "strIncreaseBtnDownTexture"));
	children.emplace_back(new StrAttribute(fdes, "strTickTexture"));
	children.emplace_back(new BoolAttribute(fdes, "thumbBtnInclusive"));
}

CT26::EffectButton::EffectButton(int fdes) : Element(fdes, "EffectButton") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new EffectButtonType(fdes, "Type"));
	children.emplace_back(new StrAttribute(fdes, "NormalTex"));
	children.emplace_back(new StrAttribute(fdes, "PushedTex"));
	children.emplace_back(new StrAttribute(fdes, "HighlightTex"));
	children.emplace_back(new StrAttribute(fdes, "EffectTex1"));
	children.emplace_back(new StrAttribute(fdes, "EffectTex2"));
}

CT26::TextListBox::TextListBox(int fdes) : Element(fdes, "TextListBox") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "maxRow"));
	children.emplace_back(new IntAttribute(fdes, "showRow"));
	children.emplace_back(new IntAttribute(fdes, "lineGap"));
	children.emplace_back(new BoolAttribute(fdes, "isShowScroll"));
}

CT26::Radar::Radar(int fdes) : Element(fdes, "Radar") {
	children.emplace_back(new DefaultProperty(fdes));
}

CT26::HtmlCtrl::HtmlCtrl(int fdes) : Element(fdes, "HtmlCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "ViewType"));
}

CT26::RadioButton::RadioButton(int fdes) : Element(fdes, "RadioButton") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "sysstring"));
	children.emplace_back(new IntAttribute(fdes, "radioGroupID"));
	children.emplace_back(new BoolAttribute(fdes, "isChecked"));
}

CT26::InvenWeight::InvenWeight(int fdes) : Element(fdes, "InvenWeight") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "Target"));
	children.emplace_back(new IntAttribute(fdes, "TextureWidth"));
	children.emplace_back(new IntAttribute(fdes, "TextureHeight"));
	children.emplace_back(new StrAttribute(fdes, "TextureStepLeft"));
	children.emplace_back(new StrAttribute(fdes, "TextureStepMid"));
	children.emplace_back(new StrAttribute(fdes, "TextureStepRight"));
	children.emplace_back(new StrAttribute(fdes, "TextureWarnLeft"));
	children.emplace_back(new StrAttribute(fdes, "TextureWarnMid"));
	children.emplace_back(new StrAttribute(fdes, "TextureWarnRight"));
	children.emplace_back(new StrAttribute(fdes, "TextureAddedLeft"));
	children.emplace_back(new StrAttribute(fdes, "TextureAddedMid"));
	children.emplace_back(new StrAttribute(fdes, "TextureAddedRight"));
	children.emplace_back(new StrAttribute(fdes, "TextureBackLeft"));
	children.emplace_back(new StrAttribute(fdes, "TextureBackMid"));
	children.emplace_back(new StrAttribute(fdes, "TextureBackRight"));
	children.emplace_back(new GaugeText(fdes));
}

CT26::BarCtrl::BarCtrl(int fdes) : Element(fdes, "BarCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "ForeTexture"));
	children.emplace_back(new StrAttribute(fdes, "ForeLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "ForeRightTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackLeftTexture"));
	children.emplace_back(new StrAttribute(fdes, "BackRightTexture"));
	children.emplace_back(new IntAttribute(fdes, "USize"));
	children.emplace_back(new IntAttribute(fdes, "VSize"));
}

CT26::ScrollArea::ScrollArea(int fdes) : Element(fdes, "ScrollArea") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new IntAttribute(fdes, "AreaHeight"));
	CT26::Schema::readChildren(fdes, children);
}

CT26::FishViewportWindow::FishViewportWindow(int fdes) : Element(fdes, "FishViewportWindow") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "texBack"));
	children.emplace_back(new StrAttribute(fdes, "texClock"));
	children.emplace_back(new StrAttribute(fdes, "texFishHPBar"));
	children.emplace_back(new StrAttribute(fdes, "texFishHPBarBack"));
	children.emplace_back(new StrAttribute(fdes, "texFishFakeHPBarWarning"));
	children.emplace_back(new StrAttribute(fdes, "texFishingEffect"));
	children.emplace_back(new StrAttribute(fdes, "texIconPumping"));
	children.emplace_back(new StrAttribute(fdes, "texIconReeling"));
}

CT26::MultiSellItemInfo::MultiSellItemInfo(int fdes) : Element(fdes, "MultiSellItemInfo") {
	children.emplace_back(new DefaultProperty(fdes));
}

CT26::MultiSellNeededItem::MultiSellNeededItem(int fdes) : Element(fdes, "MultiSellNeededItem") {
	children.emplace_back(new DefaultProperty(fdes));
}

CT26::DrawPanel::DrawPanel(int fdes) : Element(fdes, "DrawPanel") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new BoolAttribute(fdes, "AutoSize"));
}

CT26::RadarMapCtrl::RadarMapCtrl(int fdes) : Element(fdes, "RadarMapCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "MapTextureName"));
	children.emplace_back(new FloatAttribute(fdes, "Layer"));
	children.emplace_back(new List<RadarMapCtrlObjectType>(fdes));
}

CT26::RadarMapCtrlObjectType::RadarMapCtrlObjectType(int fdes) : Element(fdes, "RadarMapCtrlObjectType") {
	children.emplace_back(new StrAttribute(fdes, "TypeName"));
	children.emplace_back(new StrAttribute(fdes, "NormalTexName"));
	children.emplace_back(new StrAttribute(fdes, "PushedTexName"));
	children.emplace_back(new StrAttribute(fdes, "OverTexName"));
	children.emplace_back(new IntAttribute(fdes, "Width"));
	children.emplace_back(new IntAttribute(fdes, "Height"));
	children.emplace_back(new BoolAttribute(fdes, "Top"));
}

CT26::PropertyController::PropertyController(int fdes) : Element(fdes, "PropertyController") {
	children.emplace_back(new DefaultProperty(fdes));
}

CT26::MoviePlayerCtrl::MoviePlayerCtrl(int fdes) : Element(fdes, "MoviePlayerCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "FileName"));
	children.emplace_back(new IntAttribute(fdes, "PlayTime"));
}

CT26::FlashCtrl::FlashCtrl(int fdes) : Element(fdes, "FlashCtrl") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new StrAttribute(fdes, "FlashFile"));
}

CT26::CharacterViewportWindow::CharacterViewportWindow(int fdes) : Element(fdes, "CharacterViewportWindow") {
	children.emplace_back(new DefaultProperty(fdes));
	children.emplace_back(new FloatAttribute(fdes, "CharacterScale"));
	children.emplace_back(new IntAttribute(fdes, "CharacterOffsetX"));
	children.emplace_back(new IntAttribute(fdes, "CharacterOffsetY"));
	children.emplace_back(new IntAttribute(fdes, "CameraDistMax"));
	children.emplace_back(new IntAttribute(fdes, "CameraDistMin"));
	children.emplace_back(new IntAttribute(fdes, "DefaultCameraPitch"));
	children.emplace_back(new IntAttribute(fdes, "DefaultCameraYaw"));
	children.emplace_back(new IntAttribute(fdes, "ZoomRate"));
	children.emplace_back(new IntAttribute(fdes, "RotationRate"));
	children.emplace_back(new StrAttribute(fdes, "MaskTex"));
	children.emplace_back(new IntAttribute(fdes, "NpcID"));
}

CT26::Constant::Constant(int fdes) : Element(fdes, "Constant") {
	children.emplace_back(new List<ConstantInt>(fdes));
	children.emplace_back(new List<ConstantString>(fdes));
	children.emplace_back(new List<ConstantBool>(fdes));
	children.emplace_back(new List<ConstantFloat>(fdes));
}

CT26::ConstantInt::ConstantInt(int fdes) : Element(fdes, "ConstantInt") {
	children.emplace_back(new IntAttribute(fdes, "id"));
	children.emplace_back(new IntAttribute(fdes, "value"));
}

CT26::ConstantFloat::ConstantFloat(int fdes) : Element(fdes, "ConstantFloat") {
	children.emplace_back(new IntAttribute(fdes, "id"));
	children.emplace_back(new FloatAttribute(fdes, "value"));
}

CT26::ConstantBool::ConstantBool(int fdes) : Element(fdes, "ConstantBool") {
	children.emplace_back(new IntAttribute(fdes, "id"));
	children.emplace_back(new BoolAttribute(fdes, "value"));
}

CT26::ConstantString::ConstantString(int fdes) : Element(fdes, "ConstantString") {
	children.emplace_back(new IntAttribute(fdes, "id"));
	children.emplace_back(new StrAttribute(fdes, "value"));
}
