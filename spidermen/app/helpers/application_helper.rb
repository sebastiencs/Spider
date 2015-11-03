module ApplicationHelper
  
  def get_percent(count_type)
    return 0 if count_type == 0.0
    total = PaquetKey.count.to_s.chomp(".0").to_f + PaquetMouse.count.to_s.chomp(".0").to_f
    return ((count_type / total) * 100).to_i
  end

end
