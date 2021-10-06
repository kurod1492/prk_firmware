class RotaryEncoder
 def initialize(pin_a, pin_b)
    puts "Initializing RotaryEncoder ..."
    @pin_a = pin_a
    @pin_b = pin_b
    @rotation = 0
    @partner_keycode_cw = 0
    @partner_keycode_ccw = 0
    @split_left = true
    @proc = []
    @proc_cnt = 0
  end

  def init_pins
    init_encoder(@pin_a, @pin_b)
  end

  def create_keycodes(encoders_size)
    @partner_keycode_cw = 0b11111111 - encoders_size * 2
    @partner_keycode_ccw = @partner_keycode_cw - 1
  end

  def left?
    @split_left
  end

  def right?
    !@split_left
  end

  def configure(symbol)
    case symbol
    when :left
      @split_left = true
    when :right
      @split_left = false
    end
  end

  attr_accessor :split_left

  def read
    @rotation += read_encoder(@pin_a, @pin_b)
  end

  def clockwise(&block)
    @proc.push(block)
  end

  def call_cw
    @proc[@proc_cnt].call
  end
  def call_ccw
    @proc[@proc_cnt].call
  end
  def call_proc_if(keycode)
    case keycode
    when @partner_keycode_cw
      @proc[@proc_cnt].call
    when @partner_keycode_ccw
      @proc[@proc_cnt].call
    end
  end

  def consume_rotation_anchor
    # ignore values of 1 and -1
    if @rotation > 1 && @proc
      @proc_cnt += 1
      if(@proc.size <= @proc_cnt)
        @proc_cnt = 0
      end
      @proc[@proc_cnt].call
      sleep_ms 20
    elsif @rotation < -1 && @proc
      @proc_cnt -= 1
      if(0 > @proc_cnt)
        @proc_cnt = @proc.size - 1
      end
      @proc[@proc_cnt].call
      # counterclockwise seems more sensitive
      sleep_ms 40
    end
    @rotation = 0
  end

  def consume_rotation_partner
    # ignore values of 1 and -1
    res = if @rotation > 1 && @proc
      @partner_keycode_cw
    elsif @rotation < -1 && @proc
      @partner_keycode_ccw
    else
      0
    end
    @rotation = 0
    return res
  end
end
